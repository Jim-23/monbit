## Development Log

### v0.0.1
- ESP32 configured
- E-Ink display working
- First UI rendered

![ESP32 to display wiring](photos/display-esp-wiring.jpg)
- yes I know, I have soldered pins in a wrong direction (fixed it later)

![Display plugged in](photos/dispalay_plugged_in.jpg)
![First screen text](photos/first_screen_text.jpg)
![First UI rendered](photos/firstUI.jpg)


### Front lid

![Many tries of the front panel](photos/many_tries_of_front_panel.jpg)

#### Front lid Prototype 1 (18.6.2026)
- First enclosure top cover printed
- Learned enclosure is too small for PCB
- Screw holes tested, quite small

![First front panel - front](photos/first_front_panel-front.jpg)
![First front panel - back](photos/first_front_panel-back.jpg)

#### Front lid Prototype 2 (19.6.2026)
- Fits well, but it sits on top of the PCB, needs to be made slightly over the edge

#### Front lid Prototype 3 (19.6.2026)
- Fits well, but still I need to adjust the "back" part to have a good grid for the PCB + edges

#### Front lid Prototype 4 (19.6.2026)
- almost perfect, maybe will adjust the site a bit more
- In the future, I might make it deeper

![Fourth front panel - front](photos/4th_fron_panel-front.jpg)
![Fourth front panel - back](photos/4th_front_panel-back.jpg)

#### First button (21.6.2026)
- first button input succeeded!
- and don't forget, BUTTONS HAVE ORIENTATION!

BUTTON PRESSED
BUTTON RELEASED

![First button - works](photos/first_button.jpg)

- then I conected the display as well and added a function which refreshes the display
- when I know clikc on the button, the screen refreshes
![Display refresh](photos/display_refreshes_when_clicked.jpg)


### v.0.0.2
- first button connected to pin 0
- gui refreshment
- renamed happiness to fun so in gui is displayed F instead of second H

#### Button functions (27.6.2026)
- the button now feeds the monster by 10 until its back to 0


![Button State - hungry ](photos/feed_btn_hungry.jpg)
![Button State - less hungry](photos/feed_btn_less_hungry.jpg)

#### New GUI
- I have updated the gui to look a bit cleaner and polished, obviously its not final yet
- I had to also rename happines to fun so there are not 2 H displayed, it was quite confusing
    - I am considering to change it later to something like HUN, ENG, FUN, AGE or just use icons

![New GUI](photos/gui_update_0.jpg)


#### Update
- I have connected two more buttons and added them on pins 8, 9 and 10
- Feed button was removed and function in code as well, currently the code only prints out which button was pressed
    - LEFT
    - MIDDLE
    - RIGHT
- later, I might add more buttons, but currently this works fine
    - the breadboard is a mess, I know, but it will eventually be better.
    ![3 Buttons](photos/buttons_connected_3.jpg)
- added interaction with gui when button is pressed, for example
    - press left button => feed the Monster, 
        - hunger is decreased by 10
    - press middle button => play with the Monster
        - fun is increased by 10
        - hunger is increased by 10
        - energy is decreaased by 5
    - press right button => Monster sleeps
        - fun is decreased by 5
        - hunger is increased by 5
        - energy is increased by 10

### v.0.0.3 (28.6.2026)
- Added flash storage system
- It was quite easy actually so I am happy for that
- Saving is performed after a button is pressed
- Would like to also add an autosave every 5 minutes


### v0.0.4 (11.07.2026)

#### Audio System

- Soldered speaker to MAX98357A amplifier.
- Wired amplifier to ESP32-C3.
- Created audio module (audio.hpp and audio.cpp).
- The speaker produces buzz instead of clear tone and I have no idea why, maybe wrong I2C config
- Wiring to ESP:

    | MAX98357A | ESP32-C3 |
    |------------|----------|
    | VIN | 3.3V |
    | GND | GND |
    | DIN | GPIO0 |
    | BCLK | GPIO1 |
    | LRC (WS) | GPIO20 |
    | SD | - |
    | GAIN | -|
    | SPK+ | Speaker + |
    | SPK- | Speaker - |

#### Update (13.07.2026)
- finally managed to implement clear sound with a specific configuration
- the problem was not the HW but the config for the audio, wiring can stay as it is
- you can hear one beep sound when you power the device
![Speaker connection + spaghetti monster](photos/speaker_connection.jpg)


### v0.0.5 (14.07.2026)
- I have decided to switch to a new ESP32 module, the ESP32-S3 mostly because of more GPIO pins which I will need for accelerometer. 
  - Currently waiting for the module to arrive (approx. 2 weeks)

#### UI and Menu System
- added basic menu when middle button is pressed
- user can navigate using left button, right button and middle button to confirm
![What's on menu for today?](photos/menu_selection_v0.jpg)
