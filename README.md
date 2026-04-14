# Monbit

A tiny ESP32-based digital monster pet with an e-ink display that evolves over time based on care, sleep cycles, and randomness.

---

# Roadmap

## 0.0.1 — Hello Hardware

### Goal

* ESP32 boots
* Serial prints work
* Display shows something
* Battery powers device
* Device can charge via USB-C

### Hardware

* ESP32-C3 Development Board (WiFi + Bluetooth)
* WeAct 1.54" E-Paper Module (SPI, Black/White)
* Li-Po Battery 503035 500mAh 3.7V JST-PH 2.0
* USB-C TP4056 Lithium Battery Charger Module

### Done When

* Code uploads successfully
* Serial output works
* Display shows text or image
* Device runs from battery

---

## 0.0.2 — Input System

### Goal

* Wire buttons
* Wire power switch
* Detect button presses

### Hardware

* SKRGAED010 ALPS Tact Switch (or similar)

### Done When

* Buttons log presses
* Switch turns device on/off

---

## 0.0.3 — Memory System

### Goal

* Save current state
* Load saved state

### Done When

* Restart device
* State persists

Example:

* Hunger
* Happiness
* Energy

---

## 0.0.4 — Sound System

### Goal

* Play simple sounds
* Confirm actions with sound

### Hardware

* MAX98357A Audio Amplifier Module
* 15x3.5mm Mini Round Speaker 8Ω 0.5W

### Done When

* Device plays beep sound
* Sound triggered by button press

---

## 0.0.5 — Power Optimization

### Goal

* Deep sleep support
* Wake on button press
* Battery optimization

### Done When

* Device sleeps automatically
* Button wakes device

---

## 0.0.6 — First Monster Logic

### Goal

* Basic monster stats
* Simple interactions

Example Stats

* Hunger
* Happiness
* Energy

### Done When

* Buttons modify stats
* Display updates values

---

## 0.0.7 — UI Improvements

### Goal

* Basic UI layout
* Icons and sprites
* Monster display

### Done When

* UI readable
* Monster visible

---

## 0.1.0 — First Prototype

### Goal

* Fully assembled device
* 3D printed enclosure
* Stable hardware

### Done When

* Portable device
* Battery powered
* Fully functional
