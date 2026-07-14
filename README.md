# Monbit

A tiny ESP32-based digital monster pet with an e-ink display that evolves over time based on care, sleep cycles, and randomness.

<p align="center">
  <img src="photos/4th_fron_panel-front.jpg" alt="Monbit front panel" width="420">
</p>

## Motivation

Monbit is a personal project created to learn embedded development, hardware prototyping, and product design.

The goal is not only to create a device, but also to explore the full product development process. From firmware and electronics to CAD design and physical prototype.

I want to document the entire journey, sharing both successes and failures, to create a resource for others interested in similar projects.

---

### Documentation

- [Roadmap](./ROADMAP.md)
- [Development Log](./DEVLOG.md)
- [Hardware Notes](./hardware/hw-notes.md)
- [Game Design](./docs/game_design.md)
- [UI Design](./docs/ui_design.md)

## Current Progress

Current Version: `v0.0.4` (2026-07-13)

### Firmware
- [x] ESP32 bring-up
- [x] Project architecture (modular source files)
- [x] E-Ink display communication
- [x] Basic UI rendering
- [x] Partial display refresh
- [x] 3-button input system
- [x] Button debouncing
- [x] Monster state system
- [x] Monster actions (Feed / Play / Sleep)
- [x] Automatic monster tick system
- [x] Persistent storage (save/load)
- [x] Audio subsystem
- [ ] Battery management
- [ ] Deep sleep
- [ ] Sprite rendering
- [ ] Menu system

### Hardware
- [x] Components selected
- [x] ESP32 tested
- [x] E-Ink display tested
- [x] Buttons tested (breadboard)
- [x] First enclosure front prototype designed (front lid, far from final)
- [x] Audio amplifier connected
- [x] Speaker connected
- [ ] Battery integrated
- [ ] Charging module integrated
- [ ] Power switch integrated
- [ ] Accelerometer integrated
- [ ] Permanent wiring
- [ ] First fully assembled prototype
- [ ] Final enclosure designed

### Gameplay
- [x] Basic monster stats
- [x] Monster actions
- [x] Time-based stat changes
- [x] Beep when button is pressed
- [ ] Monster emotions
- [ ] Growth/aging system
- [ ] Evolution
- [ ] Random events
- [ ] Game balancing

### Documentation
- [x] README
- [x] Roadmap
- [x] Devlog
- [x] Project versioning
- [ ] Wiring diagrams
- [ ] Hardware BOM
- [ ] Build instructions

## Milestones

### v0.0.1 — Hello Hardware

Completed:
- ESP32-C3 configured with PlatformIO
- USB serial debugging enabled
- E-Ink display connected and initialised
- First successful display render (`MONBIT v0.0.1`)

Update:
- basic GUI setup
- connected first button

### v0.0.2 — Buttons

Completed:
- Buttons are detected and affect                    the stats
  - LEFT button => eat
  - MIDDLE button => play
  - RIGHT button => sleep
- Screen has two options for refresh - full or partial
- When the button is pressed, the screen refreshes partially (without the big blink)
- Happiness renamed to Fun

### v0.0.3 - Storage

Completed:
- Every tick (currently 10 seconds), the hunger, fun and energy are changed by 1
- Every time the button is pressed, the current state of the Monster is saved to Flash
- When rebooted, the data is loaded

### v0.0.4 - Audio

Completed:
- Audio subsystem added
- Beep when button is pressed



## Hardware

Core components:

- ESP32-C3 SuperMini
- WeAct 1.54" E-Ink Display
- 500mAh LiPo Battery
- TP4056 USB-C Charging Module

- Tactile Buttons
- MAX98357A Audio Amplifier
- Mini Speaker
- MPU6050 Accelerometer


## Software

Development environment:

- C++
- Arduino Framework
- PlatformIO
- Visual Studio Code

Libraries:

- GxEPD2


## Gallery

### Wiring & Setup

<p align="center">
  <img src="photos/display-esp-wiring.jpg" alt="ESP32 to e-ink display wiring" width="320">
  <img src="photos/dispalay_plugged_in.jpg" alt="Display plugged in" width="320">
</p>

### Display & GUI

<p align="center">
  <img src="photos/first_screen_text.jpg" alt="First screen text render" width="320">
  <img src="photos/firstUI.jpg" alt="First UI rendered on the e-ink display" width="320">
</p>
<p align="center">
  <img src="photos/gui_update_0.jpg" alt="GUI update" width="320">
</p>

### Buttons

<p align="center">
  <img src="photos/first_button.jpg" alt="First button wired" width="320">
  <img src="photos/display_refreshes_when_clicked.jpg" alt="Display refreshing on button click" width="320">
</p>
<p align="center">
  <img src="photos/feed_btn_hungry.jpg" alt="Feed button - hungry state" width="320">
  <img src="photos/feed_btn_less_hungry.jpg" alt="Feed button - less hungry state" width="320">
</p>
<p align="center">
  <img src="photos/buttons_connected_3.jpg" alt="Three buttons connected" width="320">
</p>

### Enclosure

<p align="center">
  <img src="photos/many_tries_of_front_panel.jpg" alt="Multiple front panel iterations" width="320">
</p>
<p align="center">
  <img src="photos/first_front_panel-front.jpg" alt="First front panel - front" width="320">
  <img src="photos/first_front_panel-back.jpg" alt="First front panel - back" width="320">
</p>
<p align="center">
  <img src="photos/4th_fron_panel-front.jpg" alt="Front panel - front" width="320">
  <img src="photos/4th_front_panel-back.jpg" alt="Front panel - back" width="320">
</p>

<!-- TODO: Add beauty shots once IMG_5243/5245/5247/5249/5251.HEIC are converted to .jpg/.png -->


## Repository Structure

```
monbit/
├── firmware/     # ESP32 firmware (PlatformIO)
│   ├── include/
│   ├── lib/
│   ├── src/
│   ├── test/
│   └── platformio.ini
├── hardware/     # Hardware notes & measurements
│   ├── hardware_notes.md
│   └── measurements.md
├── design/       # CAD files (enclosure STLs)
├── docs/         # Design notes
│   ├── game_design.md
│   └── ui_design.md
├── photos/       # Build & progress photos
├── DEVLOG.md
├── ROADMAP.md
├── LICENSE
└── README.md
```

---



