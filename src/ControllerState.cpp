/*
  Buttoneer <ControllerState.cpp>

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

#include "ControllerState.h"
#include "ButtoneerHID.h"
#include "constants/InputStates.h"

ControllerState::ControllerState(){
  _hid = new ButtoneerHID();
  for(int i = 0; i<32; i++)
    _buttonStates[i] = HID_OFF;
}

void ControllerState::setupEncoders(int numEncoders){
  _numEncoders = numEncoders;
  Serial.print("Setting up for thee, these encoders");
  Serial.println(_numEncoders);

  /*for(int i = 0; i<_numEncoders; i++){

  }*/
  #if(ENCODER_4 == ENC_ON)
    delay(2000);
    Serial.println("ENCODER 4 IS MARKED ON!");
  #endif
  return;

}

void ControllerState::addPush(PushEvent* ev){
  if(ev->checkForButton()){
    _hid->addPush(ev->getButton());
    ev->setPushTime();
  }
}
