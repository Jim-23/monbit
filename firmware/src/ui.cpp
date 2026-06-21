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

    constexpr int MONSTER_X = 65;
    constexpr int MONSTER_Y = 90;

    constexpr int STATS_X = MARGIN;
    constexpr int HUNGER_Y = 160;
    constexpr int ENERGY_Y = 180;

    constexpr int STAT_X_SECOND_COLUMN = 140;
    constexpr int HAPPINESS_Y = 160;
    constexpr int AGE_Y = 180;

    constexpr int FOOTER_Y = 195;
    constexpr int FOOTER_LEFT = 30;
    constexpr int FOOTER_MIDDLE = 100;
    constexpr int FOOTER_RIGHT = 160;

    constexpr char VERSION[] = "v0.0.1";
}

void draw_header()
{
    display.setFont(&FreeMonoBold9pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(ui::MARGIN, ui::HEADER_Y);
    display.printf("MONBIT %s", ui::VERSION);
}

void draw_monster()
{
    display.setCursor(ui::MONSTER_X, ui::MONSTER_Y);
    display.print("<(o_o)>");
}

void draw_stats(const Monster& monster)
{
    display.setCursor(ui::STATS_X, ui::HUNGER_Y);
    display.printf("H:%d", monster.hunger);

    display.setCursor(ui::STATS_X, ui::ENERGY_Y);
    display.printf("E:%d", monster.energy);

    display.setCursor(ui::STAT_X_SECOND_COLUMN, ui::HAPPINESS_Y);
    display.printf("H:%d", monster.happiness);

    display.setCursor(ui::STAT_X_SECOND_COLUMN, ui::AGE_Y);
    display.printf("A:%d", monster.age);
}

void draw_footer()
{
    display.setCursor(ui::FOOTER_LEFT, ui::FOOTER_Y);
    display.printf("<");

    display.fillRect(ui::FOOTER_MIDDLE, ui::FOOTER_Y - 8, 8, 8, GxEPD_BLACK);

    display.setCursor(ui::FOOTER_RIGHT, ui::FOOTER_Y);
    display.printf(">");
}

void draw_screen(const Monster& monster)
{
    display.fillScreen(GxEPD_WHITE);

    draw_header();
    draw_monster();
    draw_stats(monster);
    draw_footer();
}