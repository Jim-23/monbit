#include <Arduino.h>

void setup()
{
    //pinMode(8, OUTPUT); // blue led
    Serial.begin(115200);

    delay(1000);

    Serial.println();
    Serial.println("=== MONBIT BOOT ===");
}

void loop()
{
    Serial.println("Alive");
    delay(1000);
}