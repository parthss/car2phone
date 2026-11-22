/* SPDX-License-Identifier: Apache-2.0
 *
 * Car2Phone C API — the binding seam for HMIs that are not Qt/C++:
 * Android Automotive (JNI), Kanzi, Unreal, or an OEM's own cluster engine.
 *
 * Threading: call every function from one thread (typically the HMI thread).
 * Callbacks run inside c2p_car_poll().
 */
#ifndef C2P_H
#define C2P_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct c2p_car c2p_car;

typedef struct c2p_car_callbacks {
  void* user;
  /* state: "idle", "handshaking", "active", "fallback" */
  void (*on_state)(void* user, const char* state, const char* reason);
  /* Colours are 0xRRGGBB. Called with the OEM default theme on fallback. */
  void (*on_theme)(void* user, const char* id, const char* name, uint32_t background, uint32_t foreground,
                   uint32_t accent, const char* gauge_style);
  void (*on_nav_card)(void* user, const char* maneuver, uint32_t distance_m, const char* road, uint32_t eta_min);
  void (*on_media_card)(void* user, const char* title, const char* artist, uint32_t position_s,
                        uint32_t duration_s);
  void (*on_cards_cleared)(void* user);
} c2p_car_callbacks;

/* Loads a vehicle profile (an INI file from profiles/). Returns NULL and fills err on failure. */
c2p_car* c2p_car_create(const char* profile_path, const c2p_car_callbacks* callbacks, char* err, size_t err_len);

/* Starts listening for a phone. Returns 0 on success. Port 0 means the default (7420). */
int c2p_car_listen(c2p_car* car, uint16_t port, char* err, size_t err_len);

/* Drives networking and timers. Call at least every 50 ms. */
void c2p_car_poll(c2p_car* car, int timeout_ms);

/* Publishes a vehicle signal (COVESA VSS path) if the profile advertises it. */
void c2p_car_publish_signal(c2p_car* car, const char* vss_path, double value);

void c2p_car_destroy(c2p_car* car);

#ifdef __cplusplus
}
#endif

#endif /* C2P_H */
