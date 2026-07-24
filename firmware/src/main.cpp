#include <Arduino.h>

#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>

#include "monster.hpp"
#include "ui.hpp"
#include "input.hpp"
#include "storage.hpp"
#include "audio.hpp"

// BUSY, RST, DC, CS
GxEPD2_BW<GxEPD2_154_GDEY0154D67,
          GxEPD2_154_GDEY0154D67::HEIGHT> display(
    GxEPD2_154_GDEY0154D67(5, 4, 3, 2));

Monster monster;
Screen current_screen = Screen::Home;
int selected_menu = 0;

constexpr int MENU_ITEM_COUNT = 6;
bool needs_refresh = false;

constexpr unsigned long TICK_INTERVAL_MS = 10000;
unsigned long last_tick_ms = 0;

enum class RefreshMode
{
    Full,
    Partial
};

void refresh_display(RefreshMode mode)
{
    if (mode == RefreshMode::Full)
    {
        display.setFullWindow();
    }
    else
    {
        display.setPartialWindow(
            0,
            0,
            display.width(),
            display.height());
    }

    display.firstPage();

    do
    {
        draw_screen(monster, current_screen, selected_menu);
    }
    while (display.nextPage());

    Serial.println("Display updated");
}

void update_monster()
{
    const unsigned long now = millis();

    if (now - last_tick_ms >= TICK_INTERVAL_MS)
    {
        monster.tick();
        last_tick_ms = now;

        if (current_screen == Screen::Home)
            needs_refresh = true;

        Serial.println("Monster tick");
    }
}

void change_screen(Screen screen)
{
    current_screen = screen;
    needs_refresh = true;
}

void menu_previous()
{
    selected_menu--;

    if (selected_menu < 0)
        selected_menu = MENU_ITEM_COUNT - 1;
}

void menu_next()
{
    selected_menu++;

    if (selected_menu >= MENU_ITEM_COUNT)
        selected_menu = 0;
}

void handle_home_input(Button button)
{
    if (button == Button::Middle)
    {
        selected_menu = 0;
        change_screen(Screen::Menu);
    }
}

void execute_selected_menu()
{
    switch (selected_menu)
    {
        case MENU_FEED:
            if (monster.feed())
            {
                audio::play_feed();
                save_monster(monster);
            }

            change_screen(Screen::Home);
            break;

        case MENU_PLAY:
            if (monster.play())
            {
                audio::play_play();
                save_monster(monster);
            }

            change_screen(Screen::Home);
            break;

        case MENU_SLEEP:
            if (monster.sleep())
            {
                audio::play_sleep();
                save_monster(monster);
            }

            change_screen(Screen::Home);
            break;

        case MENU_STATS:
            change_screen(Screen::Stats);
            break;

        case MENU_SETTINGS:
            change_screen(Screen::Settings);
            break;

        case MENU_ABOUT:
            change_screen(Screen::About);
            break;
    }
}

void handle_menu_input(Button button)
{
    switch (button)
    {
        case Button::Left:
            menu_previous();
            needs_refresh = true;
            break;

        case Button::Right:
            menu_next();
            needs_refresh = true;
            break;

        case Button::Middle:
            execute_selected_menu();
            break;

        default:
            break;
    }
}

void handle_settings_input(Button button)
{
    if (button == Button::Middle)
    {
        change_screen(Screen::Home);
    }
}

void handle_about_input(Button button)
{
    if (button == Button::Middle)
    {
        change_screen(Screen::Home);
    }
}

void refresh_if_needed()
{
    if (!needs_refresh)
        return;

    refresh_display(RefreshMode::Partial);

    needs_refresh = false;
}

void handle_stats_input(Button button)
{
    if (button == Button::Middle)
    {
        change_screen(Screen::Home);
    }
}

void handle_input()
{
    const Button button = poll_buttons();

    if (button == Button::None)
        return;

    switch (current_screen)
    {
        case Screen::Home:
            handle_home_input(button);
            break;

        case Screen::Menu:
            handle_menu_input(button);
            break;

        case Screen::Stats:
            handle_stats_input(button);
            break;

        case Screen::Settings:
            handle_settings_input(button);
            break;

        case Screen::About:
            handle_about_input(button);
            break;
    }
}

void setup()
{
    Serial.begin(115200);
    Serial.println("=== MONBIT ===");

    SPI.begin(6, -1, 7, 5);

    input_init();

    display.init(115200);
    display.setRotation(0);

    if (!audio::init())
    {
        Serial.println("Audio initialization failed");
    }

    load_monster(monster);

    change_screen(Screen::Home);
    refresh_display(RefreshMode::Full);

    audio::play_startup();
}

void loop()
{

    update_monster();
    handle_input();
    refresh_if_needed();

}