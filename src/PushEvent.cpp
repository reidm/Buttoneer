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

#include "Arduino.h"
#include "PushEvent.h"
#include "constants/InputStates.h"
PushEvent::PushEvent(){
  _sensor = NULL;
  _button = NO_BUTTON;
}

void PushEvent::setSensor(SensorInterface* sensor){
  _sensor = sensor;
}

void PushEvent::setButton(int button){
  _button = button;
}

bool PushEvent::checkForButton(){
  if(_button == NO_BUTTON){
    return false;
  }
  return true;
}

int PushEvent::getButton(){
  return _button;
}
