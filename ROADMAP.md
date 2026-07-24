# Roadmap

## 0.0.1 — Hello Hardware

### Goal

* ESP32 boots
* Serial prints work
* Display shows something

### Hardware

* ESP32-C3 Development Board (WiFi + Bluetooth)
* WeAct 1.54" E-Paper Module (SPI, Black/White)

### Done When

* Code uploads successfully
* Serial output works
* Display shows text or image

**Status:** Completed

---

## 0.0.2 — Input System

### Goal

* Wire buttons
* Wire power switch
* Detect button presses
* When button pressed, do something to monster (feed it for example)

Example Stats

* Hunger
* Fun
* Energy

### Hardware

* SKRGAED010 ALPS Tact Switch

### Done When
* Basic monster stats
* Simple interactions
  
* Buttons modify stats
* Display updates values

**Status:** Completed

---

## 0.0.3 — Basic monster + Memory System

### Goal:

- Monster state changes over time
- Save current state to flash
- Load state after reboot

### Done when:
- Power off device
- Power on device
- Monster stats are restored

Example:

* Hunger
* Fun
* Energy

**Status:** Completed

---

## 0.0.4 — Sound System

### Goal

* Play simple sounds
* Confirm actions with sound

### Hardware

* MAX98357A Audio Amplifier Module
* 15x3.5mm Mini Round Speaker 8Ω 0.5W

### Done When

* The device plays a beep sound upon boot
* Sound triggered by button press

**Status:** Completed

---

## 0.0.5 — UI and Menu System

### Goal
* Create a simple menu system
* Interactive menu
* Better layout and UX

### Done When
* Menu is displayed on the screen
* Menu can be navigated with buttons
* Buttons are changed to Left Middle Right

## 0.0.6 — Monster Logic

### Goal
* Monster has a name
* Monster has a personality
* Monster logic is implemented and the monster reacts to user actions

---
## 0.0.7 — Battery integration

### Goal
* The battery powers the device
* Device can charge via USB-C
* Device can run on battery power

### Hardware
* Li-Po Battery 503035 500mAh 3.7V JST-PH 2.0
* USB-C TP4056 Lithium Battery Charger Module

### Done When
* Integrate Li-Po battery
* Integrate charging circuit
* Read battery voltage
* Display battery level

**Status:** Work in Progress

---

## 0.0.8 — Power Optimization 

### Goal

* Deep sleep support
* Wake on button press
* Switch to turn device on/off

### Done When

* Device sleeps automatically
* Button wakes the device

---
## 0.0.9 — Accelerometer Integration

### Goal
* Detect device orientation
* Detect device movement

### Hardware
* MPU6050 Accelerometer
  
### Done When
* Device detects orientation changes
* When device is moved, it reacts (e.g., wakes up, changes state, etc.)

---

## 0.0.10 — UI & Animation

### Goal

* Draw monster sprites
* Add simple animations

### Done When

* Monster is animated
* Status icons are displayed
* UI resembles the final design
  
---

## 0.0.11 — First real monster

### Goal

* Monster has a name
* Monster has a personality
* Monster has a unique appearance

### Done When

* Specific monster displays on the screen
* Monster sprite is loaded

---

## 0.0.12 — Hardware Assembly

### Goal

* All components are wired together and works without breadboard


---
## 0.0.13 — Enclosure

### Goal
* 3D printed enclosure back and front
* Enclosure holds all components
* Enclosure has holes for buttons, display, and speaker

### Done When
* All components fit inside the enclosure
* Buttons are accessible
* Display is securely mounted
* USB-C port is accessible
* Speaker opening is present

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
