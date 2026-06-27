#pragma once

#include <cstdint>

struct Monster
{
    uint8_t hunger = 40;
    uint8_t fun = 100;
    uint8_t energy = 100;
    uint16_t age = 0;

    void feed();
    void play();
    void sleep();
    void tick();
};