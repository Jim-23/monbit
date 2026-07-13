# ESP32-C3 SuperMini

## Upload

Board:
esp32-c3-devkitm-1

Monitor speed:
115200

USB:
Works on macOS with data-capable USB-C cable

## Buttons - care for monster
| Pin | activity |
|------------|----------|
| 8   | LEFT  |
| 9   | MIDDLE  |
| 10   | RIGHT  |
| 9   | -  |


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


### Audio wiring to ESP

| MAX98357A | ESP32-C3 |
|------------|----------|
| VIN | 3.3V |
| GND | GND |
| DIN | GPIO0 |
| BCLK | GPIO1 |
| LRC (WS) | GPIO20 |
| SD | NC |
| GAIN | NC |
| SPK+ | Speaker + |
| SPK- | Speaker - |

#### Working Configuration

```cpp
Sample Rate          : 22050 Hz
Bits Per Sample      : 16-bit
DMA Buffer Count     : 8
DMA Buffer Length    : 512
Channel Format       : I2S_CHANNEL_FMT_RIGHT_LEFT
Communication Format : I2S_COMM_FORMAT_STAND_I2S
Waveform             : Sine
Amplitude            : 75%
```

> **Note:** 16000 Hz also produced clean audio, but 22050 Hz was selected as the project default.
