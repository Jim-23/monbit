#include "Arduino.h"

#include "input.hpp"


namespace
{
    constexpr int FEED_BUTTON = 0;
    constexpr unsigned long DEBOUNCE_MS = 50;

    bool last_state = HIGH;
    unsigned long last_change_ms = 0;
}

bool feed_button_pressed()
{
    bool current_state = digitalRead(FEED_BUTTON);
    unsigned long now = millis();

    if (current_state != last_state)
    {
        if (now - last_change_ms >= DEBOUNCE_MS)
        {
            last_state = current_state;
            last_change_ms = now;

            return current_state == LOW;
        }
    }

    return false;
}

void input_init()
{
    pinMode(FEED_BUTTON, INPUT_PULLUP);
}