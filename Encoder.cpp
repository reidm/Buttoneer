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

Encoder encSetID(Encoder enc, int encoder_id){
  enc.encoderID = encoder_id;
  Serial.println(enc.encoderID);
  return enc;
}

Encoder encSetPins(Encoder enc, EncoderInterrupt encInt){
  enc.pinL = encInt.pinL;
  enc.pinR = encInt.pinR;
  pinMode(enc.pinL, INPUT_PULLUP);
  pinMode(enc.pinR, INPUT_PULLUP);
  Serial.print("Setting pins ");
  Serial.print(enc.pinL);
  Serial.print(" and ");
  Serial.println(enc.pinR);
  enc.valL = digitalRead(enc.pinL);
  enc.valR = digitalRead(enc.pinR);
  enc.prevL = enc.valL;
  enc.prevR = enc.valR;
  enc.pos = 12000;
  enc.lastPos = 12000;
  enc.dir = 0;
  return enc;
}

void encHandleInterrupt(Encoder enc){
  Serial.println("Handling Encoder::handleInterrupt");
  Serial.print("Reading ");
  Serial.print(enc.pinL);
  Serial.print(" and ");
  Serial.println(enc.pinR);
  enc.valL = digitalRead(enc.pinL);
  enc.valR = digitalRead(enc.pinR);
  Serial.print(enc.valL);
  /*Serial.print(" -- ");*/
  Serial.println(enc.valR);
  //Looks like it's working up to here, enable code below
  /*
  int ret = 0;
  if(enc.prevL && enc.prevR){
    if(!enc.valL && enc.valR) ret = 1;
    if(enc.valL && !enc.valR) ret = -1;
  } else if(!enc.prevL && enc.prevR){
    if(!enc.valL && !enc.valR) ret = 1;
    if(enc.valL && enc.valR) ret = -1;
  } else if(!enc.prevL && !enc.prevR){
    if(enc.valL && !enc.valR) ret = 1;
    if(!enc.valL && enc.valR) ret = -1;
  } else if(enc.prevL && !enc.prevR){
    if(enc.valL && enc.valR) ret = 1;
    if(!enc.valL && !enc.valR) ret = -1;
  }
  Serial.print(enc.pos);
  Serial.print(" - ");
  Serial.println(ret);
  Serial.print(enc.prevL);
  Serial.print(" / ");
  Serial.print(enc.prevR);
  Serial.print(" / ");
  Serial.print(enc.valL);
  Serial.print(" / ");
  Serial.println(enc.valR);

  enc.pos += ret;

  long encDiff = enc.pos - enc.lastPos;
  Serial.print("Diff is");
  Serial.println(encDiff);
  if(encDiff >= 4 || encDiff <= -4 || encDiff == 0){
    Serial.print(enc.pos);
    Serial.print(" - ");
    Serial.print(enc.lastPos);
    if (encDiff > 0){
      Serial.println("Move Ra");
      enc.dir = RIGHT;
      //_encPosition += 1;
      //addEncClick(ENCODER_AR);
    } else if (encDiff < 0){
      Serial.println("Move La");

      enc.dir = LEFT;
      //_encPosition -= 1;
      //addEncClick(ENCODER_AL);
    } else {
      if(enc.dir = RIGHT){
        Serial.println("Move Rb");
        //_encDir = RIGHT;
        //_encPosition += 1;
        //addEncClick(ENCODER_AR);
      } else if(enc.dir == LEFT){
        Serial.println("Move Lb");
        //_encDir = LEFT;
        //_encPosition -= 1;
        //addEncClick(ENCODER_AL);
       }
    }
    enc.lastPos = enc.pos;
    Serial.print(enc.pos);
    Serial.print(" - ");
    Serial.print(enc.lastPos);
    Serial.println('---');
  }

  enc.prevL = enc.valL;
  enc.prevR = enc.valR;
  */
}
/*


void volatile Encoder::handleInterrupt(){
  //Serial.println("Handling Encoder::handleInterrupt");

  _encLVal = digitalRead(_pinL);
  _encRVal = digitalRead(_pinR);
  int ret = 0;
  if(_encLPrev && _encRPrev){
    if(!_encLVal && _encRVal) ret = 1;
    if(_encLVal && !_encRVal) ret = -1;
  } else if(!_encLPrev && _encRPrev){
    if(!_encLVal && !_encRVal) ret = 1;
    if(_encLVal && _encRVal) ret = -1;
  } else if(!_encLPrev && !_encRPrev){
    if(_encLVal && !_encRVal) ret = 1;
    if(!_encLVal && _encRVal) ret = -1;
  } else if(_encLPrev && !_encRPrev){
    if(_encLVal && _encRVal) ret = 1;
    if(!_encLVal && !_encRVal) ret = -1;
  }
  Serial.print(_encPos);
  Serial.print(" - ");
  Serial.println(ret);
  _encPos += ret;
  long _encDiff = _encPos - _encLastPos;
  if(_encDiff >= 4 || _encDiff <= -4){ // || _encDiff == 0){
    Serial.print(_encPos);
    Serial.print(" - ");
    Serial.print(_encLastPos);
    if (_encDiff > 0){
      Serial.println("Move Ra");
      _encDir = RIGHT;
      //_encPosition += 1;
      //addEncClick(ENCODER_AR);
    } else if (_encDiff < 0){
      Serial.println("Move La");

      _encDir = LEFT;
      //_encPosition -= 1;
      //addEncClick(ENCODER_AL);
    } else {
      if(_encDir = RIGHT){
        Serial.println("Move Rb");
        _encDir = RIGHT;
        //_encPosition += 1;
        //addEncClick(ENCODER_AR);
      } else if(_encDir == LEFT){
        Serial.println("Move Lb");
        _encDir = LEFT;
        //_encPosition -= 1;
        //addEncClick(ENCODER_AL);
       }
    }
    _encLastPos = _encPos;
    Serial.print(_encPos);
    Serial.print(" - ");
    Serial.print(_encLastPos);
    Serial.println('---');
  }

  _encLPrev = _encLVal;
  _encRPrev = _encRVal;


}
*/
