// SPDX-License-Identifier: Apache-2.0
package org.car2phone.receiver

/** Kotlin side of jni_bridge.cpp, a thin wrapper over core/include/c2p/c2p.h. */
class CarCore(profilePath: String, private val listener: Listener) : AutoCloseable {

    interface Listener {
        fun onState(state: String, reason: String)
        fun onTheme(id: String, name: String, background: Int, foreground: Int, accent: Int, gaugeStyle: String)
        fun onNavCard(maneuver: String, distanceM: Int, road: String, etaMin: Int)
        fun onMediaCard(title: String, artist: String, positionS: Int, durationS: Int)
        fun onCardsCleared()
    }

    private var handle: Long = nativeCreate(profilePath)

    init {
        require(handle != 0L) { "could not load vehicle profile $profilePath" }
    }

    fun listen(port: Int = 7420) = check(nativeListen(handle, port) == 0) { "listen failed on port $port" }

    /** Call from one thread only; callbacks are delivered on that thread. */
    fun poll(timeoutMs: Int) = nativePoll(handle, timeoutMs, listener)

    fun publishSignal(vssPath: String, value: Double) = nativePublish(handle, vssPath, value)

    override fun close() {
        if (handle != 0L) nativeDestroy(handle)
        handle = 0L
    }

    private external fun nativeCreate(profilePath: String): Long
    private external fun nativeListen(handle: Long, port: Int): Int
    private external fun nativePoll(handle: Long, timeoutMs: Int, listener: Listener)
    private external fun nativePublish(handle: Long, vssPath: String, value: Double)
    private external fun nativeDestroy(handle: Long)

    companion object {
        init { System.loadLibrary("c2p_jni") }
    }
}
