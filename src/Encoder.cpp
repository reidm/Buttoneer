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
  _sensor = enc_int;
  _ev->setSensor(_sensor);
  Serial.println(_sensor->ioID);
  pinMode(_sensor->pinL, INPUT_PULLUP);
  pinMode(_sensor->pinR, INPUT_PULLUP);
  Serial.print("Setting pins ");
  Serial.print(_sensor->pinL);
  Serial.print(" and ");
  Serial.println(_sensor->pinR);
  _position = 12000;
  _lastPosition = 12000;
  _direction = 0;
  _subscribedTo = false;
  _prevL = _valL = digitalRead(_sensor->pinL);
  _prevR = _valR = digitalRead(_sensor->pinR);


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
    //set _ev to include direction here
    if (encDiff > 0){
      Serial.println("Move Ra");
      _ev->setButton(_sensor->buttonR);
      _sendEncoderPushToSubscriber();
      _direction = RIGHT;
    } else if (encDiff < 0){
      Serial.println("Move La");
      _ev->setButton(_sensor->buttonL);
      _sendEncoderPushToSubscriber();
      _direction = LEFT;
    } else if(_direction == LEFT){
      _ev->setButton(_sensor->buttonL);
      _sendEncoderPushToSubscriber();
      delay(2);
      _direction = RIGHT;
    } else if(_direction == RIGHT){
      _ev->setButton(_sensor->buttonR);
      _sendEncoderPushToSubscriber();
      delay(2);
      _direction = LEFT;
    }
    _lastPosition = _position;
  }

  _prevL = _valL;
  _prevR = _valR;
}


void Encoder::_sendEncoderPushToSubscriber(){
  if(_subscribedTo){
    _subscriber->addPush(_ev);
  }
}
