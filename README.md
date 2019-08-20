# Buttoneer: The Firmware

Buttoneer: The Firmware turns USB compatible Arduino boards into button box controllers. With support for buttons, switches, potentiometers and rotary encoders. Buttons inputs feature EMI protection to prevent inhuman button signals.

Supports a combination of up to 18 buttons/switches and 5 encoders.
## Planned

Potentiometer, used to set clutch axis amount for user configurable launch control.

Matrix inputs, increasing the number of buttons without using more input pins.
## Pinout - Arduino Pro Micro
```
Configurable input support:
 B  - Button/switch
 E# - Encoder (Channel 0-4)

Planned support:
 P  - Potentiometer (analog)
 B  - Button or matrix input
     -------------
E0 B | TX0   RAW |    
E0 B | RXI   GND |
     | GND   RST |
     | GND   VCC |
E1 B |  2    A3  |    BP
E1 B |  3    A2  |    BP
   B |  4    A1  |    BP
   B |  5    A0  |    BP
   B |  6    15  | E3 B
   B |  7    14  | E3 B
E2 B |  8    16  | E4 B
E2 B |  9    10  | E4 B
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
Connect B/Clk to the ENCODER_#_PIN_L pin, A/DT to ENCODER_#_PIN_R, and G to ground.

Typical encoder pinouts:
```
A/DT
        SW
G
        +
B/CLK
```

```
B/CLK
A/DT
SW
+
G
```

## Contributing
Feature and pull requests are always welcome.

## License
[GNU GENERAL PUBLIC LICENSE Version 3](https://www.gnu.org/licenses/gpl-3.0.en.html)

## Attributions
* [ArduinoJoystickLibrary](https://github.com/MHeironimus/ArduinoJoystickLibrary) by Matthew Heironimus
* [EnableInterrupt](https://github.com/GreyGnome/EnableInterrupt) By GreyGnome
* [digitalWriteFast](https://github.com/watterott/Arduino-Libs) of [Mysterious Origins](https://code.google.com/archive/p/digitalwritefast/downloads)
* [Queue](https://github.com/SMFSW/Queue) by SMFSW
