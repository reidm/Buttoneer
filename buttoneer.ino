/*
  buttoneer.ino

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

Joystick_ Joystick;

#define NUM_BUTTONS 15
#define NUM_ROTARY 1
#define NUM_POWER 1
#define ESD_COUNT 3
#define HOLD_DEBOUNCE 50
#define SAMPLE_PER_LOOP 1

#define ENCODER_HOLD 2000
#define ENCODER_DEBOUNCE 3

#define BUTTON_INST -1
#define BUTTON_OFF 0
#define BUTTON_PUSHED 1
#define BUTTON_HELD 2
#define BUTTON_PUSHED_SHORT 3
#define BUTTON_HELD_LONG 4
#define BUTTON_PUSH_THRESH 800
#define BUTTON_PUSH_LENGTH 450

//List of pins used to provide high signal
int powerSet[] = {
  15
};

//Rotary inputs, only one supported atm
//Compatible with non-interruptable pins
int rotarySet[] = {
  20, 21
};

//Output for rotaries
int rotaryDestButton[] = {
  29, 30
};

int rotary = 0;
int rotaryLastState[2*NUM_ROTARY];
int rotaryState[2*NUM_ROTARY];
int rotaryDir[NUM_ROTARY];
int rotaryOutstate[2*NUM_ROTARY];
int encoderLastDir = 0;
int encoderTimer = 0;
int encoder0Pos = 0;


int HOLD_MAP[] = {
  BUTTON_INST, 11, BUTTON_INST, BUTTON_INST, 12,
  13, 15, 17, BUTTON_INST, 22,
  23, 24, 25, BUTTON_INST, 26
};

int BUTTON_SET[] = {
  0, 1, 2, 3, 4,
  5, 6, 7, 8, 9,
  10, 14, 16, 18, 19
};

int buttonHoldCount[NUM_BUTTONS];
int buttonState[NUM_BUTTONS];
int deESD[NUM_BUTTONS];
int loopState = 0;

void setup() {
  int i = 0;
  for(i = 0; i < NUM_BUTTONS; i++){
    pinMode(BUTTON_SET[i], INPUT_PULLUP);
    deESD[i] = 0;
    buttonState[i] = 0;
  }
  for(i = 0; i < NUM_ROTARY * 2; i++){
    pinMode(rotarySet[i], INPUT_PULLUP);
    rotaryState[i] = rotaryLastState[i] = digitalRead(rotarySet[i]);
  }
  for(i= 0; i < NUM_POWER; i++){
    pinMode(powerSet[i], OUTPUT);
    digitalWrite(powerSet[i], HIGH);
  }
  Joystick.begin();
}

void loop() {
  if(digitalRead(BUTTON_SET[loopState]) == LOW){
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
  int rotAIdx = rotary*2;
  int rotBIdx = rotary*2+1;
  rotaryState[rotAIdx] = digitalRead(rotarySet[rotAIdx]);
  rotaryState[rotBIdx] = digitalRead(rotarySet[rotBIdx]);
  if ((rotaryLastState[rotAIdx] == LOW) && (rotaryState[rotAIdx] == HIGH)) {
    if (rotaryState[rotBIdx] == LOW) 
      encoder0Pos--;
    else 
      encoder0Pos++;
  }

  rotaryLastState[rotAIdx] = rotaryState[rotAIdx];
  if(encoderTimer <= 0 && encoder0Pos != 0){
    encoderTimer = ENCODER_HOLD;
    encoderPush(rotary, encoder0Pos);
    encoder0Pos = 0;
  }

  if(encoderTimer > 0){
    encoderTimer -= 1;
    if(encoderTimer == 0)
      encoderClear(rotary);
  }

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
}
