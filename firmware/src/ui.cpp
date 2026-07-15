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

    // Header
    constexpr int HEADER_Y = 18;
    constexpr int HEADER_LINE_Y = 28;

    // Monster
    constexpr int MONSTER_X = 60;
    constexpr int MONSTER_Y = 80;

    // Stats area
    constexpr int STATS_LINE_Y = 135;

    constexpr int LEFT_STATS_X = 15;
    constexpr int RIGHT_STATS_X = 115;

    constexpr int STATS_FIRST_ROW_Y = 155;
    constexpr int STATS_SECOND_ROW_Y = 175;

    // Footer
    constexpr int FOOTER_LINE_Y = 182;

    constexpr int FOOTER_Y = 197;
    constexpr int FOOTER_LEFT_X = 25;
    constexpr int FOOTER_CENTER_X = 96;
    constexpr int FOOTER_RIGHT_X = 165;

    constexpr char VERSION[] = "v0.0.4";
}

static const MenuEntry MENU[] = {
    { "Feed",     Screen::Home },
    { "Play",     Screen::Home },
    { "Sleep",    Screen::Home },
    { "Stats",    Screen::Stats },
    { "Settings", Screen::Settings },
    { "About",    Screen::About },
};

// TODO: replace ASCII monster with sprite

void draw_borders()
{
    display.drawLine(
        0,
        ui::HEADER_LINE_Y,
        ui::SCREEN_WIDTH,
        ui::HEADER_LINE_Y,
        GxEPD_BLACK
    );

    display.drawLine(
        0,
        ui::STATS_LINE_Y,
        ui::SCREEN_WIDTH,
        ui::STATS_LINE_Y,
        GxEPD_BLACK
    );

    display.drawLine(
        0,
        ui::FOOTER_LINE_Y,
        ui::SCREEN_WIDTH,
        ui::FOOTER_LINE_Y,
        GxEPD_BLACK
    );
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
    // left column
    display.setCursor(ui::LEFT_STATS_X, ui::STATS_FIRST_ROW_Y);
    display.printf("H:%d", monster.hunger);

    display.setCursor(ui::LEFT_STATS_X, ui::STATS_SECOND_ROW_Y);
    display.printf("E:%d", monster.energy);

    // right column
    display.setCursor(ui::RIGHT_STATS_X, ui::STATS_FIRST_ROW_Y);
    display.printf("F:%d", monster.fun);

    display.setCursor(ui::RIGHT_STATS_X, ui::STATS_SECOND_ROW_Y);
    display.printf("A:%d", monster.age);
}

void draw_footer()
{
    display.setCursor(ui::FOOTER_LEFT_X, ui::FOOTER_Y);
    display.print("<");

    // middle button indicator
    display.fillRect(
        ui::FOOTER_CENTER_X,
        ui::FOOTER_Y - 8,
        8,
        8,
        GxEPD_BLACK
    );

    display.setCursor(ui::FOOTER_RIGHT_X, ui::FOOTER_Y);
    display.print(">");
}

void draw_screen(const Monster& monster, Screen screen, int selected_menu)
{
    display.fillScreen(GxEPD_WHITE);
    switch (screen)
    {
        case Screen::Home:
            draw_home(monster);
            break;

        case Screen::Menu:
            draw_menu(selected_menu);
            break;

        case Screen::Stats:
            draw_stats(monster);
            break;

        case Screen::Settings:
            draw_settings();
            break;
        
        case Screen::About:
            draw_about();
            break;
    }

    
}

void draw_menu(int selected_menu)
{
    draw_header();

    int y = 50;

    for (size_t i = 0; i < sizeof(MENU) / sizeof(MenuEntry); i++)
    {
        display.setCursor(20, y);

        if ((int)i == selected_menu)
            display.print("> ");
        else
            display.print("  ");

        display.println(MENU[i].text);

        y += 20;
    }
}

void draw_home(const Monster& monster){

    draw_borders();
    draw_header();
    draw_monster();
    draw_stats(monster);
    draw_footer();
}

void draw_settings(){

}

void draw_about()
{
    draw_header();

    display.setCursor(20, 60);
    display.println("Monbit");

    display.setCursor(20, 85);
    display.println("Version 0.0.5");

    display.setCursor(20, 110);
    display.println("ESP32-C3");
}