/*
  Buttoneer <IOHandler.h>

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

#ifndef IOHandler_h
#define IOHandler_h

#include "Arduino.h"
#include "ControllerState.h"
#include "SensorInterface.h"
#include "PushEvent.h"

class IOHandler{
  public:
    IOHandler();
    void addSubscriber(ControllerState* cs);
  protected:
    PushEvent* _ev;
    void _sendPushToSubscriber();
    bool _subscribedTo;
    ControllerState* _subscriber;
    SensorInterface* _sensor;
};

#endif
