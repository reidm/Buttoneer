/*
  Buttoneer <SensorFactory.cpp>

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
#include "SensorFactory.h"

#include "../Button.h"

#include "../constants/ButtonConstants.h"
#include "../../config/ButtoneerConfig.h"

#include <EnableInterrupt.h>
#include "../../Buttoneer.h"

SensorFactory::SensorFactory(){
  _interfaceIDIterator = 0;
  _buttonCount = 0;
  _buttonIterator = 0;
  _countButtons();
}

int SensorFactory::getNumButtons(){
  return _buttonCount;
}

#include "Arduino.h"
Button** SensorFactory::getButtons(){
  Button** buttons;
  buttons = malloc(sizeof(buttons)* HW_MAX_NUM_BUTTONS);
  ButtonInterface* bi;
  #if(BUTTON_ENABLED_0 == ON)
    Serial.println("Binding button 0");
    buttons[_buttonIterator] = new Button();
    bi = new ButtonInterface();
    bi->pin = BUTTON_PIN_0;
    bi->buttonMap = BUTTON_MAP_0;
    pinMode(BUTTON_PIN_0, INPUT_PULLUP);
    enableInterrupt(BUTTON_PIN_0, interruptButton0, CHANGE);
    buttons[_buttonIterator]->addInterface(bi);
    buttons[_buttonIterator]->setID(_interfaceIDIterator);
    //b->addSubscriber(cs);
  #endif
  _interfaceIDIterator++;
  _buttonIterator++;
  #if(BUTTON_ENABLED_1 == ON)
    Serial.println("Binding button 1");
    buttons[_buttonIterator] = new Button();
    bi = new ButtonInterface();
    bi->pin = BUTTON_PIN_1;
    bi->buttonMap = BUTTON_MAP_1;
    pinMode(BUTTON_PIN_1, INPUT_PULLUP);
    enableInterrupt(BUTTON_PIN_1, interruptButton1, CHANGE);
    buttons[_buttonIterator]->addInterface(bi);
    buttons[_buttonIterator]->setID(_interfaceIDIterator);
    //b->addSubscriber(cs);
  #endif
  _interfaceIDIterator++;
  _buttonIterator++;
  return buttons;
}


void SensorFactory::_countButtons(){
  _buttonCount = BUTTON_ENABLED_0 +
    BUTTON_ENABLED_1 +
    BUTTON_ENABLED_2 +
    BUTTON_ENABLED_3 +
    BUTTON_ENABLED_4 +
    BUTTON_ENABLED_5 +
    BUTTON_ENABLED_6 +
    BUTTON_ENABLED_7 +
    BUTTON_ENABLED_8 +
    BUTTON_ENABLED_9;
}
