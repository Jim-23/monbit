#pragma once

#include <stdint.h>

namespace audio
{
    bool init();

    void beep(uint16_t frequency, uint16_t duration_ms);

    void play_startup();
    void play_feed();
    void play_play();
    void play_sleep();
}