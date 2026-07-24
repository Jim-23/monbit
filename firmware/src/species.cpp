#include "species.hpp"

#include <Arduino.h>

#include "species/cat.hpp"
#include "species/devil.hpp"
#include "species/dragon.hpp"
#include "species/fox.hpp"
#include "species/ghost.hpp"
#include "species/goat.hpp"
#include "species/gnome.hpp"
#include "species/slime.hpp"

namespace
{
    constexpr const Species* ALL_SPECIES[] =
    {
        //&species::CAT,
        //&species::DEVIL,
        //&species::DRAGON,
        //&species::FOX,
        //&species::GHOST,
        //&species::GOAT,
        //&species::GNOME,
        &species::SLIME
    };

    constexpr std::size_t SPECIES_COUNT =
        sizeof(ALL_SPECIES) / sizeof(ALL_SPECIES[0]);
}

const Species& get_species(SpeciesId id)
{
    switch (id)
    {
        case SpeciesId::Cat:
            return species::CAT;

        case SpeciesId::Devil:
            return species::DEVIL;

        case SpeciesId::Dragon:
            return species::DRAGON;

        case SpeciesId::Fox:
            return species::FOX;

        case SpeciesId::Ghost:
            return species::GHOST;

        case SpeciesId::Goat:
            return species::GOAT;

        case SpeciesId::Gnome:
            return species::GNOME;

        case SpeciesId::Slime:
            return species::SLIME;
    }

    return species::SLIME;
}

const Species& get_random_species()
{
    const std::size_t index = random(SPECIES_COUNT);
    return *ALL_SPECIES[index];
}

const char* get_random_name(const Species& species_data)
{
    if (species_data.name_count == 0)
    {
        return species_data.display_name;
    }

    const std::size_t index = random(species_data.name_count);
    return species_data.possible_names[index];
}