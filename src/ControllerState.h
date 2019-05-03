/*
  Buttoneer <ControllerState.h>

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
#ifndef ControllerState_h
#define ControllerState_h

#include "Arduino.h"

class ControllerState{
  public:
    ControllerState();
    void addPush(int button);
    void setupEncoders(int numEncoders);
  private:
    int _numEncoders;
    int _numInstantButtons;
    int _numMatrixButtons;

};

#endif
