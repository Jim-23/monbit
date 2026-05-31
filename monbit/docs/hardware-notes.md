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
WeAct 1.54"

Pins:

VCC -> 3.3V
GND -> GND
SDA -> GPIO7
SCL -> GPIO6
CS -> GPIO5
D/C -> GPIO4
RES -> GPIO3
BUSY -> GPIO2

PlatformIO:

build_flags =
    -DARDUINO_USB_MODE=1
    -DARDUINO_USB_CDC_ON_BOOT=1