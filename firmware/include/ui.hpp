#pragma once

#include "monster.hpp"

enum class Screen
{
    Home,
    Menu,
    Stats,
    Settings,
    About
};

struct MenuEntry
{
    const char* text;
    Screen destination;
};

constexpr int MENU_FEED = 0;
constexpr int MENU_PLAY = 1;
constexpr int MENU_SLEEP = 2;
constexpr int MENU_STATS = 3;
constexpr int MENU_SETTINGS = 4;
constexpr int MENU_ABOUT = 5;

void draw_header();
void draw_monster();
void draw_stats(const Monster& monster);
void draw_footer();

void draw_home(const Monster& monster);
void draw_menu(int selected_menu);
void draw_settings();
void draw_about();

void draw_screen(
    const Monster& monster,
    Screen screen,
    int selected_menu);
