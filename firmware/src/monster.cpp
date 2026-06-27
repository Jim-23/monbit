
#include "monster.hpp"

namespace
{
    uint8_t clamp_increase(uint8_t value, uint8_t amount)
    {
        return (value + amount > 100) ? 100 : value + amount;
    }

    uint8_t clamp_decrease(uint8_t value, uint8_t amount)
    {
        return (value < amount) ? 0 : value - amount;
    }
}

void Monster::feed()
{
    hunger = clamp_decrease(hunger, 10);
}

void Monster::play()
{
    energy = clamp_decrease(energy, 5);
    hunger = clamp_increase(hunger, 5);
    fun = clamp_increase(fun, 10);
}

void Monster::sleep()
{
    energy = clamp_increase(energy, 10);

    fun = clamp_decrease(fun, 5);
    hunger = clamp_increase(hunger, 5);
}

void Monster::tick()
{
    hunger++;
}