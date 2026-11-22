// SPDX-License-Identifier: Apache-2.0
#include "c2p/transport.hpp"

#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cerrno>
#include <chrono>
#include <cstring>

namespace c2p {

namespace {

#if defined(MSG_NOSIGNAL)
constexpr int kSendFlags = MSG_NOSIGNAL;
#else
constexpr int kSendFlags = 0;
#endif

void configureSocket(int fd) {
  const int one = 1;
  setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &one, sizeof(one));
#if defined(SO_NOSIGPIPE)
  setsockopt(fd, SOL_SOCKET, SO_NOSIGPIPE, &one, sizeof(one));
#endif
  const int flags = fcntl(fd, F_GETFL, 0);
  if (flags >= 0) fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

std::string errnoText(const char* what) { return std::string(what) + ": " + std::strerror(errno); }

}  // namespace

uint32_t monotonicMs() {
  using namespace std::chrono;
  return static_cast<uint32_t>(duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count());
}

// ---------------------------------------------------------------------------
TcpConnection::TcpConnection(int fd) : fd_(fd) { configureSocket(fd_); }

TcpConnection::~TcpConnection() { close(); }

void TcpConnection::close() {
  if (fd_ >= 0) {
    ::close(fd_);
    fd_ = -1;
  }
}

bool TcpConnection::send(const Frame& frame) {
  if (fd_ < 0) return false;
  const std::vector<uint8_t> bytes = encodeFrame(frame);
  size_t sent = 0;
  while (sent < bytes.size()) {
    const ssize_t n = ::send(fd_, bytes.data() + sent, bytes.size() - sent, kSendFlags);
    if (n > 0) {
      sent += static_cast<size_t>(n);
      continue;
    }
    if (n < 0 && (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR)) {
      pollfd p{fd_, POLLOUT, 0};
      if (::poll(&p, 1, 1000) <= 0) {
        error_ = "send timed out";
        close();
        return false;
      }
      continue;
    }
    error_ = errnoText("send");
    close();
    return false;
  }
  return true;
}

bool TcpConnection::send(const std::vector<Frame>& frames) {
  for (const auto& f : frames)
    if (!send(f)) return false;
  return true;
}

bool TcpConnection::receive(std::vector<Frame>& out, int timeoutMs) {
  if (fd_ < 0) return false;
  pollfd p{fd_, POLLIN, 0};
  const int ready = ::poll(&p, 1, timeoutMs);
  if (ready < 0 && errno != EINTR) {
    error_ = errnoText("poll");
    close();
    return false;
  }
  if (ready > 0) {
    uint8_t buf[16 * 1024];
    for (;;) {
      const ssize_t n = ::recv(fd_, buf, sizeof(buf), 0);
      if (n > 0) {
        decoder_.feed(buf, static_cast<size_t>(n));
        continue;
      }
      if (n == 0) {
        error_ = "peer closed the connection";
        close();
        break;
      }
      if (errno == EAGAIN || errno == EWOULDBLOCK) break;
      if (errno == EINTR) continue;
      error_ = errnoText("recv");
      close();
      break;
    }
  }
  // Deliver every complete frame, even if the peer closed right after sending.
  Frame frame;
  for (;;) {
    const auto status = decoder_.next(frame);
    if (status == FrameDecoder::Status::Ok) {
      out.push_back(std::move(frame));
      frame = Frame{};
      continue;
    }
    if (status == FrameDecoder::Status::Error) {
      error_ = "protocol error: " + decoder_.error();
      close();
    }
    break;
  }
  return fd_ >= 0;
}

// ---------------------------------------------------------------------------
TcpListener::~TcpListener() {
  if (fd_ >= 0) ::close(fd_);
}

bool TcpListener::listen(uint16_t port, std::string& error) {
  fd_ = ::socket(AF_INET, SOCK_STREAM, 0);
  if (fd_ < 0) {
    error = errnoText("socket");
    return false;
  }
  const int one = 1;
  setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
  sockaddr_in addr{};
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port = htons(port);
  if (::bind(fd_, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0 || ::listen(fd_, 4) < 0) {
    error = errnoText("bind/listen");
    ::close(fd_);
    fd_ = -1;
    return false;
  }
  return true;
}

std::unique_ptr<TcpConnection> TcpListener::accept(int timeoutMs) {
  if (fd_ < 0) return nullptr;
  pollfd p{fd_, POLLIN, 0};
  if (::poll(&p, 1, timeoutMs) <= 0) return nullptr;
  const int client = ::accept(fd_, nullptr, nullptr);
  if (client < 0) return nullptr;
  return std::make_unique<TcpConnection>(client);
}

// ---------------------------------------------------------------------------
std::unique_ptr<TcpConnection> tcpConnect(const std::string& host, uint16_t port, std::string& error) {
  addrinfo hints{};
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  addrinfo* result = nullptr;
  const std::string service = std::to_string(port);
  if (const int rc = ::getaddrinfo(host.c_str(), service.c_str(), &hints, &result); rc != 0) {
    error = std::string("resolve ") + host + ": " + gai_strerror(rc);
    return nullptr;
  }
  int fd = -1;
  for (addrinfo* ai = result; ai != nullptr; ai = ai->ai_next) {
    fd = ::socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
    if (fd < 0) continue;
    if (::connect(fd, ai->ai_addr, ai->ai_addrlen) == 0) break;
    ::close(fd);
    fd = -1;
  }
  ::freeaddrinfo(result);
  if (fd < 0) {
    error = errnoText(("connect " + host + ":" + service).c_str());
    return nullptr;
  }
  return std::make_unique<TcpConnection>(fd);
}

}  // namespace c2p
