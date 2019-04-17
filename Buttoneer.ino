/*
  Buttoneer.ino

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

#include <Joystick.h>
#include <EnableInterrupt.h>
#include <digitalWriteFast.h>
Joystick_ Joystick;

#define NUM_BUTTONS 2
#define NUM_POWER 0
#define ESD_COUNT 3
#define HOLD_DEBOUNCE 50
#define SAMPLE_PER_LOOP 2

#define BUTTON_INST -1
#define BUTTON_OFF 0
#define BUTTON_PUSHED 1
#define BUTTON_HELD 2
#define BUTTON_PUSHED_SHORT 3
#define BUTTON_HELD_LONG 4
#define BUTTON_PUSH_THRESH 800
#define BUTTON_PUSH_LENGTH 450

#define LEFT 0
#define RIGHT 1
//List of pins used to provide high signal
int powerSet[] = {};

int HOLD_MAP[] = {
  BUTTON_INST, BUTTON_INST 
};

int BUTTON_SET[] = {
  0, 1
};

int BUTTON_MATRIX_SET[] = {
  14, 16, 10
};

int buttonHoldCount[NUM_BUTTONS];
int buttonState[NUM_BUTTONS];
int deESD[NUM_BUTTONS];
int loopState = 0;

volatile bool encALVal;
volatile bool encARVal;
volatile bool encALPrev;
volatile bool encARPrev;
volatile long encAPos = 12000;
volatile bool encDir = 0;
volatile long encALastPos = 12000;
long encPosition = 0;
#define ENCODER_AL 8
#define ENCODER_AR 9

void encALHandle(){
  encARVal = digitalReadFast(ENCODER_AR);
  encALVal = digitalReadFast(ENCODER_AL);
  //encAPos += encAMove();
  encAMove();
  //Serial.println(encAPos);
  encARPrev = encARVal;
  encALPrev = encALVal;
}



int encAMove(){
  int ret = 0;
  if(encALPrev && encARPrev){
    if(!encALVal && encARVal) ret = 1;
    if(encALVal && !encARVal) ret = -1;
  } else if(!encALPrev && encARPrev){
    if(!encALVal && !encARVal) ret = 1;
    if(encALVal && encARVal) ret = -1;
  } else if(!encALPrev && !encARPrev){
    if(encALVal && !encARVal) ret = 1;
    if(!encALVal && encARVal) ret = -1;
  } else if(encALPrev && !encARPrev){
    if(encALVal && encARVal) ret = 1;
    if(!encALVal && !encARVal) ret = -1;
  } 
  encAPos += ret;
  long encADiff = encAPos - encALastPos;
  if(encADiff >= 4 || encADiff <= -4 || encADiff == 0){
    /*Serial.print(encAPos);
    Serial.print(" - ");
    Serial.print(encALastPos);*/
    if (encADiff > 0){
      addEncClick(ENCODER_AR);
    } else if (encADiff < 0){
      addEncClick(ENCODER_AL);
    } else {
      if(encDir = LEFT) addEncClick(ENCODER_AR);
      else if(encDir == RIGHT) addEncClick(ENCODER_AL);
    }
    encALastPos = encAPos;
    //encAPos = encALastPos = 12000;
  }/* else {
    Serial.print(encAPos);
    Serial.print(" - ");
    Serial.println(encALastPos);
  }*/

  return 0;
}


void setup() {
  int i = 0;
  for(i = 0; i < NUM_BUTTONS; i++){
    pinMode(BUTTON_SET[i], INPUT_PULLUP);
    deESD[i] = 0;
    buttonState[i] = 0;
  }
  for(i= 0; i < NUM_POWER; i++){
    pinMode(powerSet[i], OUTPUT);
    digitalWrite(powerSet[i], HIGH);
  }
  Joystick.begin();
  Serial.begin(115200);
  pinMode(ENCODER_AL, INPUT_PULLUP);
  pinMode(ENCODER_AR, INPUT_PULLUP);
  enableInterrupt(ENCODER_AL, encALHandle, CHANGE);
  enableInterrupt(ENCODER_AR, encALHandle, CHANGE);
  encARVal = digitalReadFast(ENCODER_AR);
  encALVal = digitalReadFast(ENCODER_AL);
  encARPrev = encARVal;
  encALPrev = encALVal;
}

void loop() {

  if(digitalReadFast(BUTTON_SET[loopState]) == LOW){
    if(HOLD_MAP[loopState] == BUTTON_INST){
      if(buttonState[loopState] == BUTTON_OFF){
        addPush(loopState);
      }
    } else {
      holdManage(loopState);
    }
  } else {
    if(buttonState[loopState] == BUTTON_PUSHED){
      remPush(loopState);
    } else if(buttonState[loopState] == BUTTON_HELD){
      addShortPush(loopState);
    } else if(buttonState[loopState] == BUTTON_PUSHED_SHORT || buttonState[loopState] == BUTTON_HELD_LONG) {
      if(buttonHoldCount[loopState] >= 1){
        buttonHoldCount[loopState] -= 1;
      }

      if(buttonHoldCount[loopState] == 0){
        buttonState[loopState] = BUTTON_OFF;
        Joystick.setButton(BUTTON_SET[loopState], LOW);
        Joystick.setButton(HOLD_MAP[loopState], LOW);
      }
    }
    deESD[loopState] = 0;
  }

  loopState += SAMPLE_PER_LOOP;
  if(loopState >= NUM_BUTTONS)
    loopState = 0;

}

void addShortPush(int button){
  buttonState[button] = BUTTON_PUSHED_SHORT;
  buttonHoldCount[button] = BUTTON_PUSH_LENGTH;
  Joystick.setButton(BUTTON_SET[button], HIGH);
}

void addLongPush(int button){
  buttonState[button] = BUTTON_HELD_LONG;
  buttonHoldCount[button] = BUTTON_PUSH_LENGTH;
  Joystick.setButton(HOLD_MAP[button], HIGH);

}
void holdManage(int button){
  if(buttonState[loopState] == BUTTON_PUSHED_SHORT || buttonState[loopState] == BUTTON_HELD_LONG){
    if(buttonHoldCount[loopState] >= 1){
      buttonHoldCount[loopState] -= 1;
    }
  } else {
    buttonHoldCount[button] += 1;
    if(buttonHoldCount[button] > HOLD_DEBOUNCE){
      buttonState[button] = BUTTON_HELD;
      if(buttonHoldCount[button] > BUTTON_PUSH_THRESH){
        addLongPush(button);
      }
    }
  }
}

void addPush(int button){
  deESD[button] += 1;
  if(deESD[button] > ESD_COUNT){
    if(buttonState[button] == BUTTON_OFF){
      if(HOLD_MAP[button] == BUTTON_INST){
        //Serial.print(button);
        Joystick.setButton(BUTTON_SET[button], HIGH);
        buttonState[button] = BUTTON_PUSHED;
      }
    }
  }
}

void remPush(int button){
  if(buttonState[button] > 0){
    Joystick.setButton(BUTTON_SET[button], LOW);
    buttonState[button] = BUTTON_OFF;
    deESD[button] = 0;

  }
}

void addEncClick(int button){
  if(button == ENCODER_AL){
    encPosition += 1;
    encDir = LEFT;
    Serial.print("L");
    Serial.println(encPosition);
  } else {
    encDir = RIGHT;
    encPosition -= 1;
    Serial.print("R");
    Serial.println(encPosition);
  }
}

/*
void encoderClear(int encoder){
  Joystick.setButton(rotaryDestButton[encoderLastDir], LOW);
  delay(ENCODER_DEBOUNCE);
  rotaryState[0] = digitalRead(rotarySet[0]);
  encoderLastDir = 0;
}

void encoderPush(int encoder, int dir){
  if( dir > 1 ) {
    dir = 1;
  } else if(dir < 0) {
    dir = 0;
  }
  if( encoderLastDir == 0 ) {
    Joystick.setButton(rotaryDestButton[dir], HIGH);
    encoderLastDir = dir;
  } else {
    encoderLastDir = 0;
  }
}*/
