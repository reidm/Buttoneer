/*
  Buttoneer <Encoder.cpp>

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

#include "Arduino.h"
#include "Encoder.h"
#include "SensorInterface.h"

Encoder::Encoder(){}

void Encoder::setup(EncoderInterface* enc_int){
<<<<<<< HEAD
  _ioID = enc_int->encoderID;
  Serial.println(_ioID);
  _buttonL = enc_int->buttonL;
  _buttonR = enc_int->buttonR;
  _pinL = enc_int->pinR;
  _pinR = enc_int->pinL;
  pinMode(_pinL, INPUT_PULLUP);
  pinMode(_pinR, INPUT_PULLUP);
=======
  _interface = enc_int;
  _ioID = enc_int->encoderID;
  Serial.println(_ioID);
  pinMode(_interface->pinL, INPUT_PULLUP);
  pinMode(_interface->pinR, INPUT_PULLUP);
>>>>>>> 1d4d12b71a073d31596a418910085cfaf8179a4a
  Serial.print("Setting pins ");
  Serial.print(_interface->pinL);
  Serial.print(" and ");
  Serial.println(_interface->pinR);
  _prevL = _valL = digitalRead(_interface->pinL);
  _prevR = _valR = digitalRead(_interface->pinR);
  _position = 12000;
  _lastPosition = 12000;
  _direction = 0;
  _subscribedTo = false;

  return;
}

int Encoder::getPosition(){
  return _position;
}


void Encoder::handleInterrupt(bool valL, bool valR){

  _valL = valL;
  _valR = valR;
  int ret = 0;
  if(_prevL && _prevR){
    if(!_valL && _valR) ret = 1;
    if(_valL && !_valR) ret = -1;
  } else if(!_prevL && _prevR){
    if(!_valL && !_valR) ret = 1;
    if(_valL && _valR) ret = -1;
  } else if(!_prevL && !_prevR){
    if(_valL && !_valR) ret = 1;
    if(!_valL && _valR) ret = -1;
  } else if(_prevL && !_prevR){
    if(_valL && _valR) ret = 1;
    if(!_valL && !_valR) ret = -1;
  }
  _position += ret;
  int encDiff = _position - _lastPosition;
  if(encDiff >= 4 || encDiff <= -4 || encDiff == 0){
    Serial.print(_position);
    Serial.print(" - ");
    Serial.print(_lastPosition);
    if (encDiff > 0){
      Serial.println("Move Ra");
<<<<<<< HEAD
      _sendEncoderPushToSubscriber(RIGHT);
      _direction = RIGHT;
    } else if (encDiff < 0){
      Serial.println("Move La");
      _sendEncoderPushToSubscriber(LEFT);
      _direction = LEFT;
    } else if(_direction == LEFT){
      _sendEncoderPushToSubscriber(RIGHT);
      delay(2);
      _direction = RIGHT;
    } else if(_direction == RIGHT){
      _sendEncoderPushToSubscriber(LEFT);
      delay(2);
=======
      _sendEncoderPushToSubscriber(_interface->buttonR);
      _direction = RIGHT;
    } else if (encDiff < 0){
      Serial.println("Move La");
      _sendEncoderPushToSubscriber(_interface->buttonL);
>>>>>>> 1d4d12b71a073d31596a418910085cfaf8179a4a
      _direction = LEFT;
    }
    _lastPosition = _position;
  }

  _prevL = _valL;
  _prevR = _valR;
}


void Encoder::_sendEncoderPushToSubscriber(int direction){
  if(_subscribedTo){
    if(direction == LEFT){
      _subscriber->addPush(_buttonL);
    } else {
      _subscriber->addPush(_buttonR);
    }
  }
}
