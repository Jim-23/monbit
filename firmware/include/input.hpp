#pragma once

enum class Button
{
    None,
    Left,
    Middle,
    Right
};

void input_init();
Button poll_buttons();