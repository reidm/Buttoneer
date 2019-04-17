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
/*
class Encoder
{
  public:
    Encoder(int pinA, int pinB);
    void move();
    void click();
  private:
    int _pin;
    volatile bool _encALVal;
    volatile bool _encARVal;
    volatile bool _encALPrev;
    volatile bool _encARPrev;
    volatile long _encAPos;
    volatile bool _encDir;
    volatile long _encALastPos;
    volatile long _encPosition;

};*/


Encoder::Encoder(int pinA, int pinB){
  Serial.println("encoder go");
}

void Encoder::move(){
  Serial.println("heyo");
}

/*
Morse::Morse(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void Morse::dot()
{
  digitalWrite(_pin, HIGH);
  delay(250);
  digitalWrite(_pin, LOW);
  delay(250);
}

void Morse::dash()
{
  digitalWrite(_pin, HIGH);
  delay(1000);
  digitalWrite(_pin, LOW);
  delay(250);
}
*/
