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
    constexpr int LEFT_MARGIN = 20;

    // Header
    constexpr int HEADER_Y = 18;
    constexpr int HEADER_LINE_Y = 28;

    // Monster
    constexpr int MONSTER_X = 60;
    constexpr int MONSTER_Y = 80;

    // Stats area
    constexpr int SCREEN_TITLE_Y = 55;
    constexpr int LINE1_Y = 85;
    constexpr int LINE2_Y = 110;
    constexpr int LINE3_Y = 135;
    constexpr int LINE4_Y = 160;

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

    constexpr char VERSION[] = "v0.0.5";
    constexpr char NAME[] = "Blob";

}

namespace sprite
{
    constexpr const char* HAPPY = "<(^‿^)>";
    constexpr const char* NORMAL = "<(^.^)>";
    constexpr const char* HUNGRY = "<(u_u)>";
    constexpr const char* TIRED = "<(=_=)>";
    constexpr const char* BORED = "<(-_-)>";
    constexpr const char* SAD = "<(._.)>";
    constexpr const char* CRITICAL = "<(T_T)>";

    constexpr const char* PLAYING = "<(^o^)>";
    constexpr const char* EATING = "<(^-^)>";
    constexpr const char* SLEEPING = "<(-.-) zZ";
    constexpr const char* DIZZY = "<(@_@)>";
    constexpr const char* SICK = "<(x_x)>";
    constexpr const char* INJURED = "<(>_<)>";
    constexpr const char* DEAD = "<(+_+)>";
}

static const MenuEntry MENU[] = 
{
    { "Feed",     Screen::Home },
    { "Play",     Screen::Home },
    { "Sleep",    Screen::Home },
    { "Stats",    Screen::Stats },
    { "Settings", Screen::Settings },
    { "About",    Screen::About },
};

//== GUI ==

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
        ui::LINE3_Y,
        ui::SCREEN_WIDTH,
        ui::LINE3_Y,
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
    display.printf("%s", ui::NAME);
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

void draw_ok_button()
{
    display.setCursor(70, 195);
    display.print("OK: Back");
}

// == MONSTER ==

void draw_monster(const Monster& monster)
{
    display.setCursor(ui::MONSTER_X, ui::MONSTER_Y);

    switch (monster.get_status())
    {
        case Status::Playing:
            display.print(sprite::PLAYING);
            return;

        // TODO add in the future draw_sprite(Sprite::Eating);

        case Status::Eating:
            display.print(sprite::EATING);
            return;

        case Status::Sleeping:
            display.print(sprite::SLEEPING);
            return;

        case Status::Dizzy:
            display.print(sprite::DIZZY);
            return;

        case Status::Sick:
            display.print(sprite::SICK);
            return;

        case Status::Injured:
            display.print(sprite::INJURED);
            return;

        case Status::Dead:
            display.print(sprite::DEAD);
            return;

        case Status::None:
            break;
    }

    switch (monster.get_mood())
    {
        case Mood::Happy:
            display.print(sprite::HAPPY);
            break;

        case Mood::Hungry:
            display.print(sprite::HUNGRY);
            break;

        case Mood::Tired:
            display.print(sprite::TIRED);
            break;

        case Mood::Bored:
            display.print(sprite::BORED);
            break;

        case Mood::Sad:
            display.print(sprite::SAD);
            break;

        case Mood::Critical:
            display.print(sprite::CRITICAL);
            break;

        case Mood::Normal:
            display.print(sprite::NORMAL);
            break;
    }
}

// == STATS ==

void draw_home_stats(const Monster& monster)
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


// == SCREENS ==

void draw_screen(const Monster& monster, Screen screen, int selected_menu)
{
    display.fillScreen(GxEPD_WHITE);
    switch (screen)
    {
        case Screen::Home:
            draw_home_screen(monster);
            break;

        case Screen::Menu:
            draw_menu_screen(selected_menu);
            break;

        case Screen::Stats:
            draw_stats_screen(monster);
            break;

        case Screen::Settings:
            draw_settings_screen();
            break;
        
        case Screen::About:
            draw_about_screen();
            break;
    }
}

void draw_home_screen(const Monster& monster)
{

    draw_borders();
    draw_header();
    draw_monster(monster);
    draw_home_stats(monster);
    draw_footer();
}

void draw_menu_screen(int selected_menu)
{
    draw_header();

    int y = 50;

    for (size_t i = 0; i < sizeof(MENU) / sizeof(MenuEntry); i++)
    {
        display.setCursor(ui::LEFT_MARGIN, y);

        if ((int)i == selected_menu)
            display.print("> ");
        else
            display.print("  ");

        display.print(MENU[i].text);

        y += 20;
    }
}

void draw_stats_screen(const Monster& monster) 
{
    draw_header();

    display.setCursor(ui::LEFT_MARGIN, ui::SCREEN_TITLE_Y);
    display.print("STATS");

    display.setCursor(ui::LEFT_MARGIN, ui::LINE1_Y);
    display.printf("Hunger: %d", monster.hunger);

    display.setCursor(ui::LEFT_MARGIN, ui::LINE2_Y);
    display.printf("Fun: %d", monster.fun);

    display.setCursor(ui::LEFT_MARGIN, ui::LINE3_Y);
    display.printf("Energy: %d", monster.energy);

    display.setCursor(ui::LEFT_MARGIN, ui::LINE4_Y);
    display.printf("Age: %d", monster.age);

    draw_ok_button();
}

void draw_settings_screen()
{
    // TODO make settings funtional
    draw_header();

    display.setCursor(ui::LEFT_MARGIN, ui::SCREEN_TITLE_Y);
    display.print("SETTINGS");

    display.setCursor(ui::LEFT_MARGIN, ui::LINE1_Y);
    display.print("Sound: ON");

    display.setCursor(ui::LEFT_MARGIN, ui::LINE2_Y);
    display.print("Change name");

    display.setCursor(ui::LEFT_MARGIN, ui::LINE3_Y);
    display.print("More soon");

    draw_ok_button();
}

void draw_about_screen()
{
    draw_header();

    display.setCursor(ui::LEFT_MARGIN, ui::SCREEN_TITLE_Y);
    display.print("ABOUT");

    display.setCursor(ui::LEFT_MARGIN, ui::LINE1_Y);
    display.print("Monbit");

    display.setCursor(ui::LEFT_MARGIN, ui::LINE2_Y);
    display.printf("Version %s", ui::VERSION);

    display.setCursor(ui::LEFT_MARGIN, ui::LINE3_Y);
    display.print("ESP32-C3");

    draw_ok_button();
}