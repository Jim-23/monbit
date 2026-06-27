
#include <Arduino.h>
#include "monster.hpp"

void Monster::feed()
{
    if (hunger == 100)
        Serial.println("Monster is full");
    else
        hunger += 10;
}