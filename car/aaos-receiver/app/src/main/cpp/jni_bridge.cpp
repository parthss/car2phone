// SPDX-License-Identifier: Apache-2.0
// JNI bridge: org.car2phone.receiver.CarCore <-> c2p.h
#include <jni.h>

#include <cstdarg>
#include <string>

#include "c2p/c2p.h"

namespace {

// Valid only during nativePoll(): callbacks fire synchronously inside c2p_car_poll().
struct PollContext {
  JNIEnv* env = nullptr;
  jobject listener = nullptr;
};
thread_local PollContext g_ctx;

jstring js(const char* s) { return g_ctx.env->NewStringUTF(s ? s : ""); }

void call(const char* name, const char* sig, ...) {
  if (!g_ctx.env || !g_ctx.listener) return;
  JNIEnv* env = g_ctx.env;
  jclass cls = env->GetObjectClass(g_ctx.listener);
  jmethodID m = env->GetMethodID(cls, name, sig);
  env->DeleteLocalRef(cls);
  if (!m) return;
  va_list args;
  va_start(args, sig);
  env->CallVoidMethodV(g_ctx.listener, m, args);
  va_end(args);
}

void onState(void*, const char* state, const char* reason) {
  jstring a = js(state), b = js(reason);
  call("onState", "(Ljava/lang/String;Ljava/lang/String;)V", a, b);
  g_ctx.env->DeleteLocalRef(a);
  g_ctx.env->DeleteLocalRef(b);
}

void onTheme(void*, const char* id, const char* name, uint32_t bg, uint32_t fg, uint32_t accent, const char* style) {
  jstring a = js(id), b = js(name), c = js(style);
  call("onTheme", "(Ljava/lang/String;Ljava/lang/String;IIILjava/lang/String;)V", a, b, (jint)bg, (jint)fg,
       (jint)accent, c);
  g_ctx.env->DeleteLocalRef(a);
  g_ctx.env->DeleteLocalRef(b);
  g_ctx.env->DeleteLocalRef(c);
}

void onNav(void*, const char* maneuver, uint32_t distance, const char* road, uint32_t eta) {
  jstring a = js(maneuver), b = js(road);
  call("onNavCard", "(Ljava/lang/String;ILjava/lang/String;I)V", a, (jint)distance, b, (jint)eta);
  g_ctx.env->DeleteLocalRef(a);
  g_ctx.env->DeleteLocalRef(b);
}

void onMedia(void*, const char* title, const char* artist, uint32_t pos, uint32_t dur) {
  jstring a = js(title), b = js(artist);
  call("onMediaCard", "(Ljava/lang/String;Ljava/lang/String;II)V", a, b, (jint)pos, (jint)dur);
  g_ctx.env->DeleteLocalRef(a);
  g_ctx.env->DeleteLocalRef(b);
}

void onCleared(void*) { call("onCardsCleared", "()V"); }

c2p_car* handleOf(jlong h) { return reinterpret_cast<c2p_car*>(h); }

}  // namespace

extern "C" {

JNIEXPORT jlong JNICALL Java_org_car2phone_receiver_CarCore_nativeCreate(JNIEnv* env, jobject, jstring path) {
  const char* p = env->GetStringUTFChars(path, nullptr);
  c2p_car_callbacks cb{};
  cb.on_state = onState;
  cb.on_theme = onTheme;
  cb.on_nav_card = onNav;
  cb.on_media_card = onMedia;
  cb.on_cards_cleared = onCleared;
  char err[256] = {0};
  c2p_car* car = c2p_car_create(p, &cb, err, sizeof(err));
  env->ReleaseStringUTFChars(path, p);
  return reinterpret_cast<jlong>(car);
}

JNIEXPORT jint JNICALL Java_org_car2phone_receiver_CarCore_nativeListen(JNIEnv*, jobject, jlong h, jint port) {
  char err[256] = {0};
  return c2p_car_listen(handleOf(h), static_cast<uint16_t>(port), err, sizeof(err));
}

JNIEXPORT void JNICALL Java_org_car2phone_receiver_CarCore_nativePoll(JNIEnv* env, jobject, jlong h, jint timeoutMs,
                                                                      jobject listener) {
  g_ctx = {env, listener};
  c2p_car_poll(handleOf(h), timeoutMs);
  g_ctx = {};
}

JNIEXPORT void JNICALL Java_org_car2phone_receiver_CarCore_nativePublish(JNIEnv* env, jobject, jlong h, jstring path,
                                                                         jdouble value) {
  const char* p = env->GetStringUTFChars(path, nullptr);
  c2p_car_publish_signal(handleOf(h), p, value);
  env->ReleaseStringUTFChars(path, p);
}

JNIEXPORT void JNICALL Java_org_car2phone_receiver_CarCore_nativeDestroy(JNIEnv*, jobject, jlong h) {
  c2p_car_destroy(handleOf(h));
}

}  // extern "C"
