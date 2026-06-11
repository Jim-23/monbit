#include "ui.hpp"

#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>

extern GxEPD2_BW<GxEPD2_154_GDEY0154D67,
                 GxEPD2_154_GDEY0154D67::HEIGHT> display;


namespace ui
{
    constexpr int SCREEN_WIDTH = 200;
    constexpr int SCREEN_HEIGHT = 200;

    constexpr int MARGIN = 10;

    constexpr int HEADER_Y = 20;
    constexpr int VERSION_Y = 40;

    constexpr int MONSTER_X = 80;
    constexpr int MONSTER_Y = 90;

    constexpr int STATS_X = MARGIN;
    constexpr int HUNGER_Y = 140;
    constexpr int ENERGY_Y = 160;
}

    constexpr char VERSION[] = "v0.0.1";
}

void draw_header()
{
    display.setFont(&FreeMonoBold9pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(ui::MARGIN, ui::HEADER_Y);
    display.print("MONBIT");
}

void draw_monster()
{
    display.setCursor(MONSTER_X, MONSTER_Y);
    display.print("(o_o)");
}

void draw_stats(const Monster& monster)
{
    display.setCursor(STATS_X, HUNGER_Y);
    display.printf("H:%d", monster.hunger);

    display.setCursor(STATS_X, ENERGY_Y);
    display.printf("E:%d", monster.energy);
}


void draw_version()
{
    display.setCursor(ui::MARGIN, ui::VERSION_Y);
    display.print(ui::VERSION);
}

void draw_footer()
{
}

void draw_screen()
{
    display.fillScreen(GxEPD_WHITE);

    draw_header();
    draw_monster();
    draw_stats();
    draw_footer();
    draw_version();
}