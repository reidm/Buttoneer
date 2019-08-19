# Buttoneer: The Firmware

Buttoneer: The Firmware turns USB compatible Arduino boards into button box controllers. With support for buttons, switches, potentiometers and rotary encoders.

## Features
Buttoneer features button, switch, and encoder support. Buttons feature virtual switching and EMI protection.

Supports up to 18 buttons/switches, 5 encoders, and 1 potentiometer.

Potentiometer can be used to set clutch axis amount for user configurable launch control.
## Pinout - Arduino Pro Micro
```
Configurable input support:
 B  - Button/switch
 M  - Matrix input
 E# - Encoder (Channel 0-4)
 P  - Potentiometer

    -------------
E0B | TX0   RAW |   
E0B | RXI   GND |
    | GND   RST |
    | GND   VCC |
E1B |  2    A3  | MPB
E1B |  3    A2  | MPB
MB  |  4    A1  | MPB
MB  |  5    A0  | MPB
MB  |  6    15  | E3B
  B |  7    14  | E3B
E2B |  8    16  | E4B
E2B |  9    10  | E4B
    -------------
```
Buttons and switches can be connected to any input. Connect one from the button/switch to GND, and the other to an input.

Each encoder reduces the button capability by 2. All input pins can also be configured as additional VCC outputs, which also reduces button capacity.

## Installation and Usage
Pre-requisites
* [Arduino IDE](https://www.arduino.cc/en/main/software)
* [ArduinoJoystickLibrary](https://github.com/MHeironimus/ArduinoJoystickLibrary)
* [EnableInterrupt](https://github.com/GreyGnome/EnableInterrupt)
* Load source ino file into Arduino IDE
* Follow [Input Configuration](#input-configuration) to set up button mappings.
* Flash your device with your version of Buttoneer.
* Once the firmware is flashed, your button box will appear as a USB Game Controller.
* Race!

## Input Configuration

## Encoder Wiring
Connect B/Clk to the ENCODER_#_PIN_L pin, A/DT to ENCODER_$_PIN_R, and G to ground.
A/DT
        SW
G
        +
B/CLK

## Contributing
Feature and pull requests are always welcome.

## License
[GNU GENERAL PUBLIC LICENSE Version 3](https://www.gnu.org/licenses/gpl-3.0.en.html)

## Attributions
* [ArduinoJoystickLibrary](https://github.com/MHeironimus/ArduinoJoystickLibrary) by Matthew Heironimus
* [EnableInterrupt](https://github.com/GreyGnome/EnableInterrupt) By GreyGnome
* [digitalWriteFast](https://github.com/watterott/Arduino-Libs) of [Mysterious Origins](https://code.google.com/archive/p/digitalwritefast/downloads)
* [Queue](https://github.com/SMFSW/Queue) by SMFSW
