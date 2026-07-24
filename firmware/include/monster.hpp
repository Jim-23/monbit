#pragma once

#include <cstdint>

#include "species.hpp"


enum class Mood
{
    Happy,
    Normal,
    Hungry,
    Tired,
    Bored,
    Sad,
    Critical
};

enum class Status
{
    None,

    Playing,
    Eating,
    Sleeping,

    Dizzy,
    Sick,
    Injured,

    Dead,
};

struct Monster
{
    SpeciesId species = SpeciesId::Slime;

    char name[16] = "Blob";

    uint8_t hunger = 0;
    uint8_t fun = 100;
    uint8_t energy = 100;
    uint16_t age = 0;

    uint16_t ticks_since_interaction = 0;

    bool feed();
    bool play();
    bool sleep();

    void tick();

    void register_interaction();

    Mood get_mood() const;
    Status get_status() const;

    Status status = Status::None;

    void set_status(Status new_status);
    void clear_status();
    bool has_status(Status expected_status) const;
    bool is_activity() const;

    const Species& get_species() const;
};

