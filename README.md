# Buttoneer: The Firmware

Buttoneer: The Firmware turns USB compatible Arduino boards into button box controllers. With support for buttons, switches, and rotary encoders.

## Features
Buttoneer fetaures button, switch, and encoder support. Buttons feature virtual switching and EMI protection.

Supports up to 18 buttons/switches, 5 encoders, and 1 potentiometer.

Potentiometer can be used to set clutch axis amount for user configurable launch control.
## Pinout
```
Input Support for Arduine Pro Micro
B - Button/switch
E1/E2 - Encoder (Channel 1 or 2)
P - Clutch Bite Point Potentiometer
    -------------
E1B | TX0   RAW |   
E1B | RXI   GND |
    | GND   RST |
    | GND   VCC |
E1B | 2     A3  |  PB
E1B | 3     A2  |  PB
  B | 4     A1  |  PB
  B | 5     A0  |  PB
  B | 6     15  | E2B
E1B | 7     14  | E2B
E2B | 8     16  | E2B
E2B | 9     10  | E2B
    -------------
```
Encoders have paired outputs, connect the pair to the same channel. Channel E1 two encoders,  E2 supports 3. Encoders will need a connection to VCC, and GND(?).

Buttons and switches can be connected to any input. Connect one from the button/switch to VCC, and the other to an input.

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


## Contributing
Feature and pull requests are always welcome.

## License
[GNU GENERAL PUBLIC LICENSE Version 3](https://www.gnu.org/licenses/gpl-3.0.en.html)

## Attributions
* [ArduinoJoystickLibrary](https://github.com/MHeironimus/ArduinoJoystickLibrary) Copyright (c) 2015, Matthew Heironimus
* [EnableInterrupt](https://github.com/GreyGnome/EnableInterrupt) By GreyGnome
