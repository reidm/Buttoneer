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

typedef struct {
  int encoderID;
  int pinL;
  int pinR;
  bool valL;
  bool valR;
  bool prevL;
  bool prevR;
  long pos = 12000;
  bool dir = 0;
  long lastPos = 12000;
} Encoder;

Encoder encSetID(Encoder enc, int encoder_id);
Encoder encSetPins(Encoder enc, EncoderInterrupt encInt);
void encHandleInterrupt(Encoder enc);

/*
class Encoder
{
  public:
    Encoder();
    void setID(int encoder_id);
    void volatile setPins(int pin_l, int pin_r);
    void volatile handleInterrupt();


  private:
    int _encoderID;
    int _pinL;
    int _pinR;
    bool volatile _encLVal;
    bool volatile _encRVal;
    bool volatile _encLPrev;
    bool volatile _encRPrev;
    long volatile _encPos = 12000;
    bool volatile _encDir = 0;
    long volatile _encLastPos = 12000;

};

*/
#endif

/*
volatile long encAPos = 12000;
volatile bool encDir = 0;
volatile long encALastPos = 12000;
long encPosition = 0;
volatile bool encALVal;
volatile bool encARVal;
volatile bool encALPrev;
volatile bool encARPrev;
volatile long encAPos;
volatile bool encDir;
volatile long encALastPos;
volatile long encPosition;
*/
