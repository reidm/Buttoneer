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
#include "ControllerState.h"

#define OFF 0
#define ON 1
#define LEFT 2
#define RIGHT 3
#define ENCODER_NUM 5
#define ENCODER_0 OFF
#define ENCODER_1 OFF
#define ENCODER_2 OFF
#define ENCODER_3 OFF
#define ENCODER_4 OFF
#define ENCODER_4_PIN_L 10
#define ENCODER_4_PIN_R 16
#define ENCODER_4_BUTTON_1 30
#define ENCODER_4_BUTTON_2 31

struct EncoderInterrupt {
  int pinL;
  int pinR;
  int encoderID;
};


class Encoder
{
  public:
    Encoder();
    void setup(EncoderInterrupt enc_int);
    void handleInterrupt(bool valL, bool valR);
    int getPosition();
    void addSubscriber(ControllerState* cs);

  private:
    void _sendToSubscriber(int button);
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
    bool _subscribedTo;
    ControllerState* _subscriber;

};

#endif
