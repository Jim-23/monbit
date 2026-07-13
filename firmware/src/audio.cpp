#include "audio.hpp"

#include <Arduino.h>
#include <driver/i2s.h>
#include <math.h>

namespace
{
    constexpr i2s_port_t I2S_PORT = I2S_NUM_0;

    constexpr gpio_num_t PIN_BCLK = GPIO_NUM_1;
    constexpr gpio_num_t PIN_LRC  = GPIO_NUM_20;
    constexpr gpio_num_t PIN_DIN  = GPIO_NUM_0;

    constexpr uint32_t SAMPLE_RATE = 22050;

    constexpr uint8_t DMA_BUFFER_COUNT = 8;
    constexpr uint16_t DMA_BUFFER_LENGTH = 512;

    constexpr int WRITE_CHUNK_FRAMES = 256;

    struct StereoFrame
    {
        int16_t left;
        int16_t right;
    };

    int16_t generate_sample(float phase)
    {
        return static_cast<int16_t>(
            sinf(2.0f * static_cast<float>(M_PI) * phase) * 32767.0f);
    }
}

bool audio::init()
{
    i2s_driver_uninstall(I2S_PORT);

    i2s_config_t config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
        .sample_rate = SAMPLE_RATE,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
        .intr_alloc_flags = 0,
        .dma_buf_count = DMA_BUFFER_COUNT,
        .dma_buf_len = DMA_BUFFER_LENGTH,
        .use_apll = false,
        .tx_desc_auto_clear = true,
        .fixed_mclk = 0
    };

    i2s_pin_config_t pins = {
        .bck_io_num = PIN_BCLK,
        .ws_io_num = PIN_LRC,
        .data_out_num = PIN_DIN,
        .data_in_num = I2S_PIN_NO_CHANGE
    };

    if (i2s_driver_install(I2S_PORT, &config, 0, nullptr) != ESP_OK)
    {
        Serial.println("Audio: driver install failed");
        return false;
    }

    if (i2s_set_pin(I2S_PORT, &pins) != ESP_OK)
    {
        Serial.println("Audio: pin configuration failed");
        return false;
    }

    Serial.println("Audio initialized");
    return true;
}

void audio::beep(uint16_t frequency, uint16_t duration_ms)
{
    const float phase_increment =
        static_cast<float>(frequency) / SAMPLE_RATE;

    const int total_frames =
        static_cast<int>((uint64_t)SAMPLE_RATE * duration_ms / 1000);

    StereoFrame chunk[WRITE_CHUNK_FRAMES];

    int written_frames = 0;

    while (written_frames < total_frames)
    {
        int frames_this_chunk = total_frames - written_frames;

        if (frames_this_chunk > WRITE_CHUNK_FRAMES)
        {
            frames_this_chunk = WRITE_CHUNK_FRAMES;
        }

        for (int i = 0; i < frames_this_chunk; i++)
        {
            float phase = fmodf(
                (written_frames + i) * phase_increment,
                1.0f);

            int16_t value =
                static_cast<int16_t>(generate_sample(phase) * 0.75f);

            chunk[i] = { value, value };
        }

        size_t bytes_written;

        i2s_write(
            I2S_PORT,
            chunk,
            frames_this_chunk * sizeof(StereoFrame),
            &bytes_written,
            portMAX_DELAY);

        written_frames += frames_this_chunk;
    }
}

void audio::play_startup()
{
    beep(440, 80);
    delay(20);

    beep(660, 80);
    delay(20);

    beep(880, 120);
}

void audio::play_feed()
{
    beep(900, 60);
}

void audio::play_play()
{
    beep(700, 70);
    delay(20);

    beep(900, 70);
}

void audio::play_sleep()
{
    beep(220, 180);
}