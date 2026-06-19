# Monbit

A tiny ESP32-based digital monster pet with an e-ink display that evolves over time based on care, sleep cycles, and randomness.

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

Current Version: `v0.0.1`

### Firmware
- [x] ESP32 bring-up
- [x] E-Ink display communication
- [ ] Button input system
- [ ] Sound output
- [ ] Persistent storage

### Hardware
- [x] Components selected
- [x] Display wired
- [x] First enclosure prototype designed
- [ ] Battery integration
- [ ] Button wiring
- [ ] Final enclosure prototype
  


## Milestones

### v0.0.1 — Hello Hardware ✅

Completed:

- ESP32-C3 configured with PlatformIO
- USB serial debugging enabled
- E-Ink display connected and initialized
- First successful display render (`MONBIT v0.0.1`)


## Hardware

Core components:

- ESP32-C3 SuperMini
- WeAct 1.54" E-Ink Display
- 500mAh LiPo Battery
- TP4056 USB-C Charging Module

Planned components:

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


## Repository Structure

```
monbit/
├── firmware/     # ESP32 firmware
├── hardware/     # CAD files, photos, wiring
├── docs/         # Design notes
├── DEVLOG.md
├── ROADMAP.md
└── README.md
```

---



