#include <Arduino.h>

void setup()
{
    Serial.begin(115200);
    delay(2000);

    Serial.println("=== MONBIT BOOTS ===");
}

void loop()
{
    Serial.println("ALIVE");
    delay(1000);
}