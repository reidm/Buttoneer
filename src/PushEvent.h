/*
  Buttoneer <PushEvent.h>

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
#ifndef PushEvent_h
#define PushEvent_h

#include "Arduino.h"
#include "interfaces/SensorInterface.h"

#define NO_BUTTON -1

class PushEvent{
  public:
    PushEvent();
    void setSensor(SensorInterface* sensor);
    void resetButton();
    void setButton(int button);
    void setPushTime();
    unsigned long getPushTime();
    int getButton();
    int getLastButton();
    bool checkForButton();
    bool isEncoderEvent();
  private:
    SensorInterface* _sensor;
    int _button;
    int _lastButton;
    unsigned long _pushTime;

};

#endif
