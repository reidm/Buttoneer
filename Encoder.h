/*
  Buttoneer <Encoder.h>

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
#ifndef Encoder_h
#define Encoder_h

#include "Arduino.h"

#define LEFT 0
#define RIGHT 1
#define ENCODER_NUM 5
#define ENCODER_4_L 10
#define ENCODER_4_R 16


struct EncoderInterrupt {
  int pinL;
  int pinR;
  int encoderID;
};


class Encoder2
{
  public:
    Encoder2();
    void setID(int encoder_id);
    void setPins(int pin_l, int pin_r);
    void handleInterrupt(bool valL, bool valR);
    int getPosition();

  private:
    int _encoderID;
    int _pinL;
    int _pinR;
    bool _valL;
    bool _valR;
    int _position;
    int _lastPosition;
    bool _prevL;
    bool _prevR;
    bool _direction;
};

#endif
