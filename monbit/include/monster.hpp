#pragma once

#include <cstdint>

struct Monster
{
    uint8_t hunger;
    uint8_t happiness;
    uint8_t energy;

    uint16_t age;

    Monster();
};