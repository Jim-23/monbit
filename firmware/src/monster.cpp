
#include "monster.hpp"

// TODO consider renaming hunger to something else, its confusing tah H is bad when 100 but others are good

namespace
{
    constexpr uint8_t MAX_STAT = 100;
    constexpr uint8_t MIN_STAT = 0;

    constexpr uint8_t FEED_AMOUNT = 10;
    constexpr uint8_t PLAY_ENERGY_COST = 10;
    constexpr uint8_t PLAY_FUN_GAIN = 5;
    constexpr uint8_t PLAY_HUNGER_GAIN = 5;

    constexpr uint8_t SLEEP_ENERGY_GAIN = 10;
    constexpr uint8_t SLEEP_FUN_LOSS = 5;
    constexpr uint8_t SLEEP_HUNGER_GAIN = 5;

    constexpr uint8_t TICK_HUNGER_GAIN = 1;
    constexpr uint8_t TICK_FUN_LOSS = 1;
    constexpr uint8_t TICK_ENERGY_LOSS = 1;

    uint8_t increase_stat(uint8_t value, uint8_t amount)
    {
        return (value + amount > MAX_STAT)
            ? MAX_STAT
            : value + amount;
    }

    uint8_t decrease_stat(uint8_t value, uint8_t amount)
    {
        return (value < amount)
            ? MIN_STAT
            : value - amount;
    }
}


void Monster::feed()
{
    hunger = decrease_stat(hunger, FEED_AMOUNT);
}

void Monster::play()
{
    if (energy >= 10)
    {
        energy = decrease_stat(energy, PLAY_ENERGY_COST);
        hunger = increase_stat(hunger, PLAY_HUNGER_GAIN);
        fun = increase_stat(fun, PLAY_FUN_GAIN);
    }
}

void Monster::sleep()
{
    energy = increase_stat(energy, SLEEP_ENERGY_GAIN);

    fun = decrease_stat(fun, SLEEP_FUN_LOSS);
    hunger = increase_stat(hunger, SLEEP_HUNGER_GAIN);
}

void Monster::tick()
{
    hunger = increase_stat(hunger, TICK_HUNGER_GAIN);
    fun = decrease_stat(fun, TICK_FUN_LOSS);
    energy = decrease_stat(energy, TICK_ENERGY_LOSS);
}