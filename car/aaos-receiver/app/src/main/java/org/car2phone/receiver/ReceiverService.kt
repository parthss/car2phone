// SPDX-License-Identifier: Apache-2.0
package org.car2phone.receiver

import android.app.Notification
import android.app.NotificationChannel
import android.app.NotificationManager
import android.app.Service
import android.car.Car
import android.car.VehiclePropertyIds
import android.car.hardware.CarPropertyValue
import android.car.hardware.property.CarPropertyManager
import android.content.Intent
import android.os.Handler
import android.os.HandlerThread
import android.os.IBinder
import android.util.Log
import java.io.File

/**
 * Runs the Car2Phone core on a worker thread and feeds it read-only vehicle data.
 * Skeleton: theme/card callbacks are logged; a real build renders them on the
 * center/passenger screens (store build) or hands them to the OEM cluster HMI.
 */
class ReceiverService : Service(), CarCore.Listener {

    private lateinit var worker: HandlerThread
    private lateinit var handler: Handler
    private var core: CarCore? = null
    private var car: Car? = null
    @Volatile private var speedKmh = 0.0

    override fun onCreate() {
        super.onCreate()
        startForeground(1, notification())

        // TODO: the OEM integration build ships the real profile; the store build
        // asks the head unit for its display layout. Default: Harman Ignite / Tata.
        val profile = File(filesDir, "vehicle.ini")
        if (!profile.exists()) assets.open(DEFAULT_PROFILE).use { input ->
            profile.outputStream().use { input.copyTo(it) }
        }

        worker = HandlerThread("car2phone-core").also { it.start() }
        handler = Handler(worker.looper)
        handler.post {
            core = CarCore(profile.absolutePath, this).also { it.listen() }
            handler.post(::loop)
        }
        subscribeToSpeed()
    }

    private fun loop() {
        val c = core ?: return
        c.poll(0)
        c.publishSignal("Vehicle.Speed", speedKmh)
        handler.postDelayed(::loop, 16)
    }

    private fun subscribeToSpeed() {
        car = Car.createCar(this)
        val props = car?.getCarManager(Car.PROPERTY_SERVICE) as? CarPropertyManager ?: return
        props.registerCallback(object : CarPropertyManager.CarPropertyEventCallback {
            override fun onChangeEvent(value: CarPropertyValue<*>) {
                speedKmh = ((value.value as? Float) ?: 0f) * 3.6 // m/s -> km/h
            }
            override fun onErrorEvent(propId: Int, zone: Int) {}
        }, VehiclePropertyIds.PERF_VEHICLE_SPEED, CarPropertyManager.SENSOR_RATE_NORMAL)
    }

    override fun onDestroy() {
        handler.post { core?.close(); core = null }
        worker.quitSafely()
        car?.disconnect()
        super.onDestroy()
    }

    override fun onBind(intent: Intent?): IBinder? = null

    private fun notification(): Notification {
        val nm = getSystemService(NotificationManager::class.java)
        nm.createNotificationChannel(NotificationChannel("c2p", "Car2Phone", NotificationManager.IMPORTANCE_LOW))
        return Notification.Builder(this, "c2p")
            .setContentTitle("Car2Phone")
            .setContentText("Waiting for phone")
            .setSmallIcon(android.R.drawable.stat_sys_data_bluetooth)
            .build()
    }

    // ---- CarCore.Listener (called on the worker thread) ----
    override fun onState(state: String, reason: String) = log("state $state ($reason)")
    override fun onTheme(id: String, name: String, background: Int, foreground: Int, accent: Int, gaugeStyle: String) =
        log("theme $name ($id)")
    override fun onNavCard(maneuver: String, distanceM: Int, road: String, etaMin: Int) =
        log("nav $maneuver in $distanceM m onto $road")
    override fun onMediaCard(title: String, artist: String, positionS: Int, durationS: Int) =
        log("media $title - $artist")
    override fun onCardsCleared() = log("cards cleared")

    private fun log(msg: String) {
        Log.i("Car2Phone", msg)
    }

    companion object {
        const val DEFAULT_PROFILE = "tata-harrier-ev.ini"
    }
}
