#include "debug_audio.hpp"

#include <Arduino.h>
#include <driver/i2s.h>
#include <math.h>

namespace
{
    constexpr i2s_port_t I2S_PORT = I2S_NUM_0;

    constexpr gpio_num_t PIN_BCLK = GPIO_NUM_1;
    constexpr gpio_num_t PIN_LRC  = GPIO_NUM_20;
    constexpr gpio_num_t PIN_DIN  = GPIO_NUM_0;

    using W = audio::Waveform;

    // Configs to cycle through on boot.
    // Columns: sample_rate, dma_buf_count, dma_buf_len, channel_format, comm_format, waveform, amplitude, label
    constexpr audio::Config TEST_CONFIGS[] = {
        { 44100, 8, 512, I2S_CHANNEL_FMT_RIGHT_LEFT, I2S_COMM_FORMAT_STAND_I2S,       W::Sine,     0.75f, "44100 stereo I2S     sine     75%" },
        { 44100, 8, 512, I2S_CHANNEL_FMT_ALL_LEFT,   I2S_COMM_FORMAT_STAND_I2S,       W::Sine,     0.75f, "44100 mono   I2S     sine     75%" },
        { 44100, 8, 512, I2S_CHANNEL_FMT_RIGHT_LEFT, I2S_COMM_FORMAT_STAND_MSB,       W::Sine,     0.75f, "44100 stereo MSB     sine     75%" },
        { 22050, 8, 512, I2S_CHANNEL_FMT_RIGHT_LEFT, I2S_COMM_FORMAT_STAND_I2S,       W::Sine,     0.75f, "22050 stereo I2S     sine     75%" },
        { 16000, 8, 512, I2S_CHANNEL_FMT_RIGHT_LEFT, I2S_COMM_FORMAT_STAND_I2S,       W::Sine,     0.75f, "16000 stereo I2S     sine     75%" },
        { 44100, 8, 256, I2S_CHANNEL_FMT_RIGHT_LEFT, I2S_COMM_FORMAT_STAND_I2S,       W::Sine,     0.75f, "44100 stereo I2S     sine     buf=256" },
        { 44100, 4, 512, I2S_CHANNEL_FMT_RIGHT_LEFT, I2S_COMM_FORMAT_STAND_I2S,       W::Sine,     0.75f, "44100 stereo I2S     sine     dma=4" },
        { 44100, 8, 512, I2S_CHANNEL_FMT_RIGHT_LEFT, I2S_COMM_FORMAT_STAND_I2S,       W::Square,   0.40f, "44100 stereo I2S     square   40%" },
        { 44100, 8, 512, I2S_CHANNEL_FMT_RIGHT_LEFT, I2S_COMM_FORMAT_STAND_I2S,       W::Triangle, 0.75f, "44100 stereo I2S     triangle 75%" },
        { 44100, 8, 512, I2S_CHANNEL_FMT_RIGHT_LEFT, I2S_COMM_FORMAT_STAND_I2S,       W::Sawtooth, 0.40f, "44100 stereo I2S     sawtooth 40%" },
        { 44100, 8, 512, I2S_CHANNEL_FMT_RIGHT_LEFT, I2S_COMM_FORMAT_STAND_PCM_SHORT, W::Sine,     0.75f, "44100 stereo PCM_S   sine     75%" },
    };

    // Chunk size for batched writes (number of stereo frames per write call)
    constexpr int WRITE_CHUNK_FRAMES = 256;
}

bool audio::init(const Config& cfg)
{
    // Uninstall previous driver if already running
    i2s_driver_uninstall(I2S_PORT);

    i2s_config_t config = {
        .mode                 = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
        .sample_rate          = cfg.sample_rate,
        .bits_per_sample      = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format       = cfg.channel_format,
        .communication_format = cfg.comm_format,
        .intr_alloc_flags     = 0,
        .dma_buf_count        = cfg.dma_buf_count,
        .dma_buf_len          = cfg.dma_buf_len,
        .use_apll             = false,
        .tx_desc_auto_clear   = true,
        .fixed_mclk           = 0
    };

    i2s_pin_config_t pins = {
        .bck_io_num   = PIN_BCLK,
        .ws_io_num    = PIN_LRC,
        .data_out_num = PIN_DIN,
        .data_in_num  = I2S_PIN_NO_CHANGE
    };

    if (i2s_driver_install(I2S_PORT, &config, 0, nullptr) != ESP_OK)
        return false;

    if (i2s_set_pin(I2S_PORT, &pins) != ESP_OK)
        return false;

    return true;
}

static int16_t generate_sample(audio::Waveform waveform, float phase)
{
    // phase in [0, 1)
    float s;
    switch (waveform)
    {
        case audio::Waveform::Square:
            s = phase < 0.5f ? 1.0f : -1.0f;
            break;
        case audio::Waveform::Triangle:
            s = (phase < 0.5f) ? (4.0f * phase - 1.0f)
                               : (3.0f - 4.0f * phase);
            break;
        case audio::Waveform::Sawtooth:
            s = 2.0f * phase - 1.0f;
            break;
        case audio::Waveform::Sine:
        default:
            s = sinf(2.0f * (float)M_PI * phase);
            break;
    }
    return (int16_t)(s * 32767.0f);
}

// Writes a tone in chunks to avoid per-sample DMA overhead.
void audio::play_test_tone(uint32_t sample_rate, float frequency_hz, uint32_t duration_ms,
                            Waveform waveform, float amplitude)
{
    // Each frame = left + right channel (stereo layout)
    struct StereoFrame { int16_t left; int16_t right; };

    const float scale = amplitude < 0.0f ? 0.0f : (amplitude > 1.0f ? 1.0f : amplitude);
    const float phase_inc = frequency_hz / (float)sample_rate;
    const int   total_frames = (int)((uint64_t)sample_rate * duration_ms / 1000);
    StereoFrame chunk[WRITE_CHUNK_FRAMES];

    int written_frames = 0;
    while (written_frames < total_frames)
    {
        int frames_this_chunk = total_frames - written_frames;
        if (frames_this_chunk > WRITE_CHUNK_FRAMES)
            frames_this_chunk = WRITE_CHUNK_FRAMES;

        for (int i = 0; i < frames_this_chunk; i++)
        {
            float phase = fmodf((written_frames + i) * phase_inc, 1.0f);
            int16_t v = (int16_t)(generate_sample(waveform, phase) * scale);
            chunk[i] = { v, v };
        }

        size_t bytes_written = 0;
        i2s_write(I2S_PORT,
                  chunk,
                  frames_this_chunk * sizeof(StereoFrame),
                  &bytes_written,
                  portMAX_DELAY);

        written_frames += frames_this_chunk;
    }
}

void audio::run_config_tests()
{
    constexpr int NUM_CONFIGS = sizeof(TEST_CONFIGS) / sizeof(TEST_CONFIGS[0]);

    Serial.println("--- Audio config test start ---");

    for (int i = 0; i < NUM_CONFIGS; i++)
    {
        const Config& cfg = TEST_CONFIGS[i];
        Serial.printf("[%d/%d] %s\n", i + 1, NUM_CONFIGS, cfg.label);

        if (!init(cfg))
        {
            Serial.println("  init FAILED, skipping");
            continue;
        }

        // 440 Hz A note, then 880 Hz A5 — easier to distinguish quality
        play_test_tone(cfg.sample_rate, 440.0f, 500, cfg.waveform, cfg.amplitude);
        delay(200);
        play_test_tone(cfg.sample_rate, 880.0f, 500, cfg.waveform, cfg.amplitude);
        delay(600); // pause between configs so you can tell them apart
    }

    Serial.println("--- Audio config test done ---");
}
