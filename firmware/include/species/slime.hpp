#pragma once

#include "species.hpp"

namespace species
{
    inline constexpr const char* SLIME_NAMES[] =
    {
        "Blob",
        "Bloop",
        "Goop",
        "Jelly",
        "Mochi",
        "Pudding"
    };

    inline constexpr Species SLIME =
    {
        SpeciesId::Slime,
        "Slime",

        SLIME_NAMES,
        sizeof(SLIME_NAMES) / sizeof(SLIME_NAMES[0]),

        Food::Berry,
        Food::Meat,

        0.8f, // hunger rate
        0.9f, // fun rate
        1.0f  // energy rate
    };
}