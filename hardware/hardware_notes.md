# ESP32-C3 SuperMini

## Upload

Board:
esp32-c3-devkitm-1

Monitor speed:
115200

USB:
Works on macOS with data-capable USB-C cable

## Display

Display:
WeAct 1.54" E-Paper

### Display Wiring to ESP

| WeAct E-Ink | ESP32-C3 |
|------------|----------|
| VCC        | 3.3V     |
| GND        | GND      |
| SDA        | GPIO7    |
| SCL        | GPIO6    |
| CS         | GPIO5   |
| DC          | GPIO4    |
| RES        | GPIO3    |
| BUSY       | GPIO2    |


PlatformIO:

build_flags =
    -DARDUINO_USB_MODE=1
    -DARDUINO_USB_CDC_ON_BOOT=1

Driver:

GxEPD2_154_GDEY0154D67

SPI:

SPI.begin(6, -1, 7, 5);