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

#include "Encoder.h"
#include "SensorInterface.h"

Encoder::Encoder(){}

void Encoder::setup(EncoderInterface* enc_int){
  _interface = enc_int;
  _ev->setSensor(_interface);
  Serial.println(_interface->ioID);
  pinMode(_interface->pinL, INPUT_PULLUP);
  pinMode(_interface->pinR, INPUT_PULLUP);
  Serial.print("Setting pins ");
  Serial.print(_interface->pinL);
  Serial.print(" and ");
  Serial.println(_interface->pinR);
  _position = 12000;
  _lastPosition = 12000;
  _direction = 0;
  _subscribedTo = false;
  _prevL = _valL = digitalRead(_interface->pinL);
  _prevR = _valR = digitalRead(_interface->pinR);


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
      _ev->setButton(_interface->buttonMapR);
      _sendEncoderPushToSubscriber();
      _direction = RIGHT;
    } else if (encDiff < 0){
      Serial.println("Move La");
      _ev->setButton(_interface->buttonMapL);
      _sendEncoderPushToSubscriber();
      _direction = LEFT;
    } else if(_direction == LEFT){
      _ev->setButton(_interface->buttonMapR);
      _direction = RIGHT;
      _sendEncoderPushToSubscriber();
    } else if(_direction == RIGHT){
      _direction = LEFT;
      _ev->setButton(_interface->buttonMapL);
      _sendEncoderPushToSubscriber();
    }
    _lastPosition = _position;
  }

  _prevL = _valL;
  _prevR = _valR;
}


void Encoder::_sendEncoderPushToSubscriber(){
  if(_subscribedTo){
    Serial.println("Encoder is subscribed to, adding push event");
    _subscriber->addPush(_ev);
  }
}
