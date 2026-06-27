#include <Arduino.h>

#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>

#include "monster.hpp"
#include "ui.hpp"
#include "input.hpp"

// BUSY, RST, DC, CS
GxEPD2_BW<GxEPD2_154_GDEY0154D67, GxEPD2_154_GDEY0154D67::HEIGHT> display(
    GxEPD2_154_GDEY0154D67(5, 4, 3, 2));

Monster monster;


void refresh_display(bool full = false)
{
    // TODO periodically refresh fully display after some time
    if (full)
        display.setFullWindow();
    else
        display.setPartialWindow(0, 0, display.width(), display.height());

    display.firstPage();
    do
    {
        draw_screen(monster);
    } while (display.nextPage());

    Serial.println("Display updated");
}


void setup()
{
    Serial.begin(115200);
    Serial.println("=== MONBIT BOOTS ===");

    SPI.begin(6, -1, 7, 5);

    input_init();

    display.init(115200);
    display.setRotation(0);

    refresh_display(true);
}



void loop()
{
    Button button = poll_buttons();

    switch (button)
    {
        case Button::Left:
            Serial.println("LEFT");
            break;

        case Button::Middle:
            Serial.println("MIDDLE");
            break;

        case Button::Right:
            Serial.println("RIGHT");
            break;

        case Button::None:
            break;
    }
}