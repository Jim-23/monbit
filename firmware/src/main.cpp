#include <Arduino.h>

#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>

#include "monster.hpp"
#include "ui.hpp"

// BUSY, RST, DC, CS
GxEPD2_BW<GxEPD2_154_GDEY0154D67, GxEPD2_154_GDEY0154D67::HEIGHT> display(
    GxEPD2_154_GDEY0154D67(5, 4, 3, 2));


void setup()
{
    Serial.begin(115200);
    Serial.println("=== MONBIT BOOTS ===");

    SPI.begin(6, -1, 7, 5);

    display.init(115200);

    display.setRotation(0);

    display.setFullWindow();

    Monster monster;
    display.firstPage();
    do
    {
        
        draw_screen(monster);

    } while (display.nextPage());

        Serial.println("Display updated");
    }

void loop()
{
}