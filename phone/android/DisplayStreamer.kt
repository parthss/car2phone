// SPDX-License-Identifier: Apache-2.0
// SKETCH (not built): one encoder pipeline per car display granted VIDEO.
package org.car2phone.phone

import android.content.Context
import android.hardware.display.DisplayManager
import android.hardware.display.VirtualDisplay
import android.media.MediaCodec
import android.media.MediaCodecInfo
import android.media.MediaFormat
import android.view.Surface

/**
 * Renders into a VirtualDisplay sized to the car's screen and hands encoded
 * access units to [sink], which frames them on channel 0x10 + displayId.
 */
class DisplayStreamer(
    private val context: Context,
    private val displayId: Int,
    private val width: Int,
    private val height: Int,
    private val fps: Int = 60,
    private val bitrate: Int = 12_000_000,
    private val sink: (displayId: Int, data: ByteArray, isKeyFrame: Boolean, ptsUs: Long) -> Unit,
) {
    private var codec: MediaCodec? = null
    private var inputSurface: Surface? = null
    private var virtualDisplay: VirtualDisplay? = null

    fun start() {
        val format = MediaFormat.createVideoFormat(MediaFormat.MIMETYPE_VIDEO_HEVC, width, height).apply {
            setInteger(MediaFormat.KEY_COLOR_FORMAT, MediaCodecInfo.CodecCapabilities.COLOR_FormatSurface)
            setInteger(MediaFormat.KEY_BIT_RATE, bitrate)
            setInteger(MediaFormat.KEY_FRAME_RATE, fps)
            setInteger(MediaFormat.KEY_I_FRAME_INTERVAL, 1)
            setInteger(MediaFormat.KEY_LATENCY, 0) // low-latency hint (API 30+)
        }
        val c = MediaCodec.createEncoderByType(MediaFormat.MIMETYPE_VIDEO_HEVC)
        c.setCallback(object : MediaCodec.Callback() {
            override fun onInputBufferAvailable(codec: MediaCodec, index: Int) = Unit // surface input
            override fun onOutputBufferAvailable(codec: MediaCodec, index: Int, info: MediaCodec.BufferInfo) {
                codec.getOutputBuffer(index)?.let { buf ->
                    val bytes = ByteArray(info.size)
                    buf.position(info.offset)
                    buf.get(bytes)
                    val key = info.flags and MediaCodec.BUFFER_FLAG_KEY_FRAME != 0
                    sink(displayId, bytes, key, info.presentationTimeUs)
                }
                codec.releaseOutputBuffer(index, false)
            }
            override fun onError(codec: MediaCodec, e: MediaCodec.CodecException) = stop()
            override fun onOutputFormatChanged(codec: MediaCodec, format: MediaFormat) = Unit
        })
        c.configure(format, null, null, MediaCodec.CONFIGURE_FLAG_ENCODE)
        inputSurface = c.createInputSurface()
        c.start()
        codec = c

        val dm = context.getSystemService(DisplayManager::class.java)
        virtualDisplay = dm.createVirtualDisplay(
            "car2phone-display-$displayId", width, height, 160, inputSurface,
            DisplayManager.VIRTUAL_DISPLAY_FLAG_PRESENTATION,
        )
        // Show content with android.app.Presentation(context, virtualDisplay.display).
    }

    fun stop() {
        virtualDisplay?.release(); virtualDisplay = null
        codec?.run { stop(); release() }; codec = null
        inputSurface?.release(); inputSurface = null
    }
}
