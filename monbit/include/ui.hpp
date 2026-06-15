#pragma once

#include "monster.hpp"

void draw_header();
void draw_monster();
void draw_stats(const Monster& monster);
void draw_footer();

void draw_screen(const Monster& monster);