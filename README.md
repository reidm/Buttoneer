# Buttoneer: The Firmware

Buttoneer: The Firmware turns USB compatible Arduino boards into button box controllers. With support for buttons, switches, and rotary encoders.

## Features
Push buttons feature debounce and EMI protection.

The encoder function totally works ok despite relying on polling.

## Configuration
-------------
   B0 | TX0   RAW |    
   B1 | RXI   GND |
      | GND   RST |
      | GND   VCC |
   B2 |  2    A3  | E0
   B3 |  3    A2  | E0
   B4 |  4    A1  |
   B5 |  5    A0  | Pot  
   B6 |  6    15  | E1
   B7 |  7    14  | E1
B8/10 |  8    16  | E2
B9/10 |  9    10  | E2
-------------

Wire up buttons/switches to any or all of pins: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 14, 16, 18, 19

Wire a single optional encoder to pins: 20, 21

Nota: Pins 8+9 are connected to their own buttons, and also to button 10. Each pin has a 1n4001 diode to isolate their individual buttons.
Follow
## Installation
Pre-requisites
* [Arduino IDE](https://www.arduino.cc/en/main/software)
* [ArduinoJoystickLibrary](https://github.com/MHeironimus/ArduinoJoystickLibrary)
* Flash firmware using Arduino IDE
* Done!

## Usage
Once configured and installed, just plug your wheel in. It will appear as a USB Game Controller.

## Contributing
Feature and pull requests are always welcome.

## License
[GNU GENERAL PUBLIC LICENSE Version 3](https://www.gnu.org/licenses/gpl-3.0.en.html)

## Attributions
[ArduinoJoystickLibrary](https://github.com/MHeironimus/ArduinoJoystickLibrary) Copyright (c) 2015, Matthew Heironimus
