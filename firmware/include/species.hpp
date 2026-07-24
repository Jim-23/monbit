#pragma once

#include <cstddef>
#include <cstdint>

enum class SpeciesId : uint8_t
{
    Cat,
    Devil,
    Dragon,
    Fox,
    Ghost,
    Goat,
    Gnome,
    Slime
};

enum class Food : uint8_t
{
    Berry,
    Fish,
    Meat,
    Vegetable,
    Sweet,
    Mushroom
};

struct Species
{
    SpeciesId id;
    const char* display_name;

    const char* const* possible_names;
    std::size_t name_count;

    Food favorite_food;
    Food disliked_food;

    float hunger_rate;
    float fun_rate;
    float energy_rate;
};

const Species& get_species(SpeciesId id);
const Species& get_random_species();
const char* get_random_name(const Species& species_data);