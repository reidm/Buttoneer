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
#include "SensorInterface.h"
#include "IOHandler.h"
#include "ControllerState.h"
#include "constants/EncoderConstants.h"


class Encoder:public IOHandler{
  public:
    Encoder();
    void setup(EncoderInterface* enc_int);
    void handleInterrupt(bool valL, bool valR);
    int getPosition();

  private:
    void _sendEncoderPushToSubscriber();
    EncoderInterface* _interface;
    bool _valL;
    bool _valR;
    int _position;
    int _lastPosition;
    bool _prevL;
    bool _prevR;
    bool _direction;

};

#endif
