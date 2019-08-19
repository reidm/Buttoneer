/*
  Buttoneer <PushEvent.cpp>

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

#include "PushEvent.h"
#include "constants/InputStates.h"
PushEvent::PushEvent(){
  _sensor = NULL;
  resetButton();
  setPushTime();
}

bool PushEvent::isEncoderEvent(){
  if (_sensor->interfaceType == ENCODER_INTERFACE)
    return true;
  return false;
}

void PushEvent::setSensor(SensorInterface* sensor){
  _sensor = sensor;
}

void PushEvent::resetButton(){
  _lastButton = _button;
  _button = NO_BUTTON;
}

void PushEvent::setButton(int button){
  _lastButton = _button;
  _button = button;
}

void PushEvent::setPushTime(){
  _pushTime = millis();
}

unsigned long PushEvent::getPushTime(){
  return _pushTime;
}

bool PushEvent::checkForButton(){
  if(_button == NO_BUTTON){
    return false;
  }
  unsigned long now = millis();
  if (now - _pushTime < RETRIGGER_TIMER){
    Serial.println("Button press timed out (still active)");
    return false;
  }
  return true;
}

int PushEvent::getButton(){
  return _button;
}

int PushEvent::getLastButton(){
  return _lastButton;
}
