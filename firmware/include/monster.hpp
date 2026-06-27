#pragma once

#include <cstdint>

struct Monster
{
    uint8_t hunger = 0;
    uint8_t happiness = 100;
    uint8_t energy = 100;
    uint16_t age = 0;

    void feed();
    void play();
    void sleep();
    void tick();
};