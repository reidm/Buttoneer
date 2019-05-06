/*
  Buttoneer <ButtoneerHID.cpp>

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
#include "ButtoneerHID.h"
#include "PushEvent.h"
#include <Joystick.h>
Joystick_ Joystick;

ButtoneerHID::ButtoneerHID(){
  _hid = &Joystick;
  _hid->begin();
  for(int i = 0; i<32; i++)
    _buttonState[i] = BUTTON_OFF;
}

void ButtoneerHID::addPush(int button){
  if(!_buttonOn(button)){
    _buttonState[button] = BUTTON_ON;
    Serial.print("HID Push: ");
    Serial.println(button);
    _hid->setButton(button, HIGH);
  }
}

void ButtoneerHID::_removePush(int button){
  _buttonState[button] = BUTTON_OFF;
  _hid->setButton(button, LOW);
}

bool ButtoneerHID::_buttonOn(int button){
    if(_buttonState[button] == BUTTON_ON)
      return true;
    return false;
}
