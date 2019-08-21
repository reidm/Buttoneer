/*
  Buttoneer <SensorInterface.h>

  Copyright (c) 2019, Reid Miller

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef SensorInterface_h
#define SensorInterface_h

#define ENCODER_INTERFACE 10
#define BUTTON_INTERFACE 11

class SensorInterface{
  public:
    int interfaceType;
};

class EncoderInterface:public SensorInterface{
  public:
    EncoderInterface();
    int pinL;
    int pinR;
    int buttonMapL;
    int buttonMapR;
};

class ButtonInterface:public SensorInterface{
  public:
    ButtonInterface();
    int pin;
    int buttonMap;
};

#endif
