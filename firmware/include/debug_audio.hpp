#pragma once

#include <cstdint>
#include <driver/i2s.h>

namespace audio
{
    enum class Waveform { Sine, Square, Triangle, Sawtooth };

    struct Config
    {
        uint32_t           sample_rate;
        uint8_t            dma_buf_count;
        uint16_t           dma_buf_len;
        i2s_channel_fmt_t  channel_format;
        i2s_comm_format_t  comm_format;
        Waveform           waveform;
        float              amplitude;   // 0.0 – 1.0
        const char*        label;
    };

    bool init(const Config& cfg);
    void play_test_tone(uint32_t sample_rate, float frequency_hz, uint32_t duration_ms,
                        Waveform waveform, float amplitude);
    void run_config_tests();
}