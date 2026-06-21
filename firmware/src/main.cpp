#include <Arduino.h>

#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>

#include "monster.hpp"
#include "ui.hpp"

// BUSY, RST, DC, CS
GxEPD2_BW<GxEPD2_154_GDEY0154D67, GxEPD2_154_GDEY0154D67::HEIGHT> display(
    GxEPD2_154_GDEY0154D67(5, 4, 3, 2));

constexpr int BUTTON_PIN = 0;

bool last_state = HIGH;


void setup()
{
    Serial.begin(115200);
    Serial.println("=== MONBIT BOOTS ===");

    SPI.begin(6, -1, 7, 5);

    display.init(115200);

    pinMode(BUTTON_PIN, INPUT_PULLUP);

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
    bool current_state = digitalRead(BUTTON_PIN);

    if (current_state != last_state)
    {
        if (current_state == LOW)
        {
            Serial.println("BUTTON PRESSED");
        }
        else
        {
            Serial.println("BUTTON RELEASED");
        }

        last_state = current_state;
    }
}