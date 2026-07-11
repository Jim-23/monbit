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
        draw_screen(monster);
    }
    while (display.nextPage());

    Serial.println("Display updated");
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
        Serial.println("Audio init failed");
    }
    else
    {
        Serial.println("Audio initialized");
    }

    load_monster(monster);

    refresh_display(RefreshMode::Full);

    audio::play_test_tone();
}

void loop()
{
    bool needs_refresh = false;
    unsigned long now = millis();

    if (now - last_tick_ms >= TICK_INTERVAL_MS)
    {
        monster.tick();
        last_tick_ms = now;
        needs_refresh = true;

        Serial.println("Monster tick");
    }

    Button button = poll_buttons();

    switch (button)
    {
        case Button::Left:
            monster.feed();
            save_monster(monster);
            needs_refresh = true;
            break;

        case Button::Middle:
            monster.play();
            save_monster(monster);
            needs_refresh = true;
            break;

        case Button::Right:
            monster.sleep();
            save_monster(monster);
            needs_refresh = true;
            break;

        case Button::None:
            break;
    }

    if (needs_refresh)
    {
        refresh_display(RefreshMode::Partial);
        needs_refresh = false;
    }
}