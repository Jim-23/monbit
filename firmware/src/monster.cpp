
#include "monster.hpp"

// TODO consider renaming hunger to something else, its confusing tah H is bad when 100 but others are good

namespace
{
    constexpr uint16_t SAD_TICKS = 30;

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

    constexpr uint8_t CRITICAL_HUNGER = 90;
    constexpr uint8_t LOW_STAT = 20;
    constexpr uint8_t HAPPY_HUNGER_MAX = 25;
    constexpr uint8_t HAPPY_STAT_MIN = 70;

    constexpr uint8_t HUNGRY_THRESHOLD = 70;
    constexpr uint8_t BORED_THRESHOLD = 40;
    constexpr uint8_t TIRED_THRESHOLD = 40;


    uint8_t increase_stat(uint8_t value, uint8_t amount)
    {
        return (value > MAX_STAT - amount)
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

// == INTERACTIONS ==

bool Monster::feed()
{
    if (hunger == MIN_STAT){
        return false;
    }

    hunger = decrease_stat(hunger, FEED_AMOUNT);
    set_status(Status::Eating);
    register_interaction();

    return true;
}

bool Monster::play()
{
    if (energy < PLAY_ENERGY_COST || fun == MAX_STAT)
    {
        return false;
    }

    energy = decrease_stat(energy, PLAY_ENERGY_COST);
    hunger = increase_stat(hunger, PLAY_HUNGER_GAIN);
    fun = increase_stat(fun, PLAY_FUN_GAIN);

    set_status(Status::Playing);
    register_interaction();

    return true;
}

bool Monster::sleep()
{
    if (energy == MAX_STAT)
    {
        return false;
    }

    energy = increase_stat(energy, SLEEP_ENERGY_GAIN);
    fun = decrease_stat(fun, SLEEP_FUN_LOSS);
    hunger = increase_stat(hunger, SLEEP_HUNGER_GAIN);

    set_status(Status::Sleeping);
    register_interaction();

    return true;
}


// === SPECIES ===
const Species& Monster::get_species() const
{
    return ::get_species(species);
}

// === TICKS ===
void Monster::tick()
{
    if (is_activity())
    {
        clear_status();
    }

    hunger = increase_stat(hunger, TICK_HUNGER_GAIN);
    fun = decrease_stat(fun, TICK_FUN_LOSS);
    energy = decrease_stat(energy, TICK_ENERGY_LOSS);

    if (ticks_since_interaction < UINT16_MAX)
    {
        ticks_since_interaction++;
    }
}


// === HELPERS ===

void Monster::register_interaction()
{
    ticks_since_interaction = 0;
}

Mood Monster::get_mood() const
{
    if (hunger >= CRITICAL_HUNGER || fun <= LOW_STAT || energy <= LOW_STAT)
    {
        return Mood::Critical;
    }

    if (ticks_since_interaction >= SAD_TICKS)
    {
        return Mood::Sad;
    }

    if (hunger >= HUNGRY_THRESHOLD) 
    {
        return Mood::Hungry;
    }

    if (energy <= TIRED_THRESHOLD)
    {
        return Mood::Tired;
    }

    if (fun <= BORED_THRESHOLD)
    {
        return Mood::Bored;
    }
    
    if (hunger <= HAPPY_HUNGER_MAX && fun >= HAPPY_STAT_MIN && energy >= HAPPY_STAT_MIN)
    {
        return Mood::Happy;
    }

    return Mood::Normal;
}

Status Monster::get_status() const
{
    return status;
}

void Monster::set_status(Status new_status)
{
    status = new_status;
}

void Monster::clear_status()
{
    status = Status::None;
}

bool Monster::has_status(Status expected_status) const
{
    return status == expected_status;
}

bool Monster::is_activity() const
{
    return status == Status::Playing || status == Status::Eating || status == Status::Sleeping;
}