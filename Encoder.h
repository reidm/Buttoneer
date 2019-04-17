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


class Encoder
{
  public:
    Encoder(int pinA, int pinB);
    void move();
    //void click();
  private:
    int _pin;
    volatile bool encALVal;
    volatile bool encARVal;
    volatile bool encALPrev;
    volatile bool encARPrev;
    volatile long encAPos;
    volatile bool encDir;
    volatile long encALastPos;
    volatile long encPosition;

};


#endif


/*

volatile bool encALVal;
volatile bool encARVal;
volatile bool encALPrev;
volatile bool encARPrev;
volatile long encAPos = 12000;
volatile bool encDir = 0;
volatile long encALastPos = 12000;
long encPosition = 0;

*/
