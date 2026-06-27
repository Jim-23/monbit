#include "Arduino.h"

#include "input.hpp"

#include "input.hpp"
#include <Arduino.h>

namespace
{
    constexpr int LEFT_BUTTON = 8;
    constexpr int MIDDLE_BUTTON = 9;
    constexpr int RIGHT_BUTTON = 10;

    constexpr unsigned long DEBOUNCE_MS = 50;

    bool last_left_state = HIGH;
    bool last_middle_state = HIGH;
    bool last_right_state = HIGH;

    unsigned long last_left_change = 0;
    unsigned long last_middle_change = 0;
    unsigned long last_right_change = 0;
}

bool check_button(
    int pin,
    bool& last_state,
    unsigned long& last_change)
{
    bool current_state = digitalRead(pin);
    unsigned long now = millis();

    if (current_state != last_state)
    {
        if (now - last_change >= DEBOUNCE_MS)
        {
            last_state = current_state;
            last_change = now;

            return current_state == LOW;
        }
    }

    return false;
}

void input_init()
{
    pinMode(LEFT_BUTTON, INPUT_PULLUP);
    pinMode(MIDDLE_BUTTON, INPUT_PULLUP);
    pinMode(RIGHT_BUTTON, INPUT_PULLUP);
}

Button poll_buttons()
{
    if (check_button(
            LEFT_BUTTON,
            last_left_state,
            last_left_change))
    {
        return Button::Left;
    }

    if (check_button(
            MIDDLE_BUTTON,
            last_middle_state,
            last_middle_change))
    {
        return Button::Middle;
    }

    if (check_button(
            RIGHT_BUTTON,
            last_right_state,
            last_right_change))
    {
        return Button::Right;
    }

    return Button::None;
}