#include "storage.hpp"

#include <Preferences.h>

namespace
{
    Preferences preferences;
}

void save_monster(const Monster& monster)
{
    preferences.begin("monbit", false);

    preferences.putUChar("hunger", monster.hunger);
    preferences.putUChar("fun", monster.fun);
    preferences.putUChar("energy", monster.energy);
    preferences.putUShort("age", monster.age);

    preferences.end();
}

void load_monster(Monster& monster)
{
    preferences.begin("monbit", true);

    monster.hunger = preferences.getUChar("hunger", 0);
    monster.fun = preferences.getUChar("fun", 100);
    monster.energy = preferences.getUChar("energy", 100);
    monster.age = preferences.getUShort("age", 0);

    preferences.end();
}