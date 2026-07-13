#include "audio.hpp"

#include <Arduino.h>
#include <driver/i2s.h>
#include <math.h>

namespace
{
    constexpr i2s_port_t I2S_PORT = I2S_NUM_0;

    constexpr gpio_num_t PIN_BCLK = GPIO_NUM_1;
    constexpr gpio_num_t PIN_LRC = GPIO_NUM_20;
    constexpr gpio_num_t PIN_DIN = GPIO_NUM_0;

    constexpr uint32_t SAMPLE_RATE = 16000; //44100;
}

bool audio::init()
{
    i2s_config_t config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
        .sample_rate = SAMPLE_RATE,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
        .intr_alloc_flags = 0,
        .dma_buf_count = 8,
        .dma_buf_len = 64,
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
        return false;

    if (i2s_set_pin(I2S_PORT, &pins) != ESP_OK)
        return false;

    return true;
}

void audio::play_test_tone()
{
    constexpr float FREQUENCY = 440.0f;
    constexpr int DURATION_MS = 500;

    struct StereoSample
    {
        int16_t left;
        int16_t right;
    };

    const int samples = SAMPLE_RATE * DURATION_MS / 1000;

    for (int i = 0; i < samples; i++)
    {
        float t = (float)i / SAMPLE_RATE;

        int16_t value =
            (int16_t)(sinf(2.0f * PI * FREQUENCY * t) * 12000);

        StereoSample sample = {
            value,
            value
        };

        size_t written;
        i2s_write(
            I2S_PORT,
            &sample,
            sizeof(sample),
            &written,
            portMAX_DELAY);
    }
}
