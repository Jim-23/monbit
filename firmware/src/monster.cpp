
#include <Arduino.h>
#include "monster.hpp"

void Monster::feed()
{
    if (hunger == 0)
        Serial.println("Monster is full");
    else
        hunger -= 10;
}

void Monster::play()
{
    if (energy >= 10)
    {
        energy -= 10;
        happiness += 5;
    }
}

void Monster::sleep()
{
    energy = 100;
}

void Monster::tick()
{
    hunger++;
}