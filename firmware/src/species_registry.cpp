#include "species_registry.hpp"

#include "species/slime.hpp"

const Species& get_species(SpeciesId id)
{
    switch (id)
    {
        case SpeciesId::Slime:
            return species::SLIME;

        default:
            return species::SLIME;
    }
}

const Species& get_random_species()
{
    return species::SLIME;
}