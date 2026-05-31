#include <Arduino.h>

#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>

// BUSY, RST, DC, CS
GxEPD2_BW<GxEPD2_154_GDEY0154D67, GxEPD2_154_GDEY0154D67::HEIGHT> display(
    GxEPD2_154_GDEY0154D67(5, 4, 3, 2));


namespace ui
{
    constexpr int SCREEN_WIDTH = 200;
    constexpr int SCREEN_HEIGHT = 200;

    constexpr int MARGIN = 10;

    constexpr int HEADER_Y = 20;
    constexpr int VERSION_Y = 40;

    constexpr int MONSTER_X = 50;
    constexpr int MONSTER_Y = 90;

    constexpr char VERSION[] = "v0.0.1";
}

void draw_header()
{
    display.setFont(&FreeMonoBold9pt7b);
    display.setCursor(ui::MARGIN, ui::HEADER_Y);
    display.print("MONBIT");
}

void draw_version()
{
    display.setCursor(ui::MARGIN, ui::VERSION_Y);
    display.print(ui::VERSION);
}

void draw_screen()
{
    display.fillScreen(GxEPD_WHITE);

    display.setTextColor(GxEPD_BLACK);

    draw_header();
    draw_version();
}

void setup()
{
    Serial.begin(115200);
    Serial.println("=== MONBIT BOOTS ===");

    SPI.begin(6, -1, 7, 5);

    display.init(115200);

    display.setRotation(0);

    display.setFullWindow();
    display.firstPage();
  do
  {
    
    draw_screen();

  } while (display.nextPage());

    Serial.println("Display updated");
}

void loop()
{
}