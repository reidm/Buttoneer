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

#define ESD_COUNT 2

#define SAMPLE_PER_LOOP 1

#define ENCODER_HOLD 2000
#define ENCODER_DEBOUNCE 1

#define BUTTON_HOLD 1500
#define BUTTON_INST 0

//Inputs pins used for buttons
int buttonHoldTime[] = {
  BUTTON_INST, BUTTON_HOLD, BUTTON_INST, BUTTON_INST, BUTTON_HOLD,
  BUTTON_HOLD, BUTTON_HOLD, BUTTON_HOLD, BUTTON_INST, BUTTON_HOLD,
  BUTTON_HOLD, BUTTON_HOLD, BUTTON_HOLD, BUTTON_INST, BUTTON_HOLD
};

int buttonHoldMap[] = {
  BUTTON_INST, 11, BUTTON_INST, BUTTON_INST, 12,
  13, 15, 17, BUTTON_INST, 22,
  23, 24, 25, BUTTON_INST, 26
};

int buttonSet[] = {
  0, 1, 2, 3, 4,
  5, 6, 7, 8, 9,
  10, 14, 16, 18, 19
};
int buttonHoldCount[NUM_BUTTONS];
int buttonState[NUM_BUTTONS];
int deESD[NUM_BUTTONS];
int debounce[NUM_BUTTONS];
int loopState = 0;
int state;
int rotary = 0;



//Rotary inputs, only one supported atm
//Compatible with non-interruptable pins
int rotarySet[] = {
  20, 21
};

int rotaryLastState[2*NUM_ROTARY];
int rotaryState[2*NUM_ROTARY];
int rotaryDir[NUM_ROTARY];
int rotaryOutstate[2*NUM_ROTARY];
int encoderLastDir = 0;
int encoderTimer = 0;

//Output for rotaries
int rotaryDestButton[] = {
  29, 30
};



int encoder0Pos = 0;

//List of pins used to provide high signal
int powerSet[] = {
  15
};

void setup() {
  int i = 0;
  for(i = 0; i < NUM_BUTTONS; i++){
    pinMode(buttonSet[i], INPUT_PULLUP);
    deESD[i] = 0;
    debounce[i] = 0;
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
  //for(int i = loopState; i <= loopState + SAMPLE_PER_LOOP && i < NUM_BUTTONS; i++){
  state = digitalRead(buttonSet[loopState]);
  if (state == LOW) { //  && checkDebounce(loopState)){
    addPush(loopState, false);
  } else if (state == HIGH){
    /*if(buttonState[loopState] != 1){
      addPush(loopState, true);
    } else {8*/
     remPush(loopState);
    /*}(*/
  }
  //}
  loopState += SAMPLE_PER_LOOP;
  if (loopState >= NUM_BUTTONS)
    loopState = 0;
  
  int rotAIdx = rotary*2;
  int rotBIdx = rotary*2+1;
  rotaryState[rotAIdx] = digitalRead(rotarySet[rotAIdx]);
  rotaryState[rotBIdx] = digitalRead(rotarySet[rotBIdx]);
  if((rotaryLastState[rotAIdx] == LOW) && (rotaryState[rotAIdx] == HIGH)) {
    if (rotaryState[rotBIdx] == LOW) {
      encoder0Pos--;
    } else {
      encoder0Pos++;
    }

  }

  rotaryLastState[rotAIdx] = rotaryState[rotAIdx];
  if(encoderTimer <= 0 && encoder0Pos != 0){

    encoderTimer = ENCODER_HOLD;
    encoderPush(rotary, encoder0Pos);
    encoder0Pos = 0;
  }


  if(encoderTimer > 0){
    encoderTimer -= 1;
    if(encoderTimer == 0){
      encoderClear(rotary);
    }
  }



}

void encoderClear(int encoder){
  Joystick.setButton(rotaryDestButton[encoderLastDir], LOW);
  delay(ENCODER_DEBOUNCE);
  rotaryState[0] = digitalRead(rotarySet[0]);
  encoderLastDir = 0;
}

void encoderPush(int encoder, int dir){
  if(dir > 1 ) {
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

void remPush(int button){
  if (buttonState[button] == 1){
    Joystick.setButton(buttonSet[button], LOW);
    Joystick.setButton(buttonHoldMap[button], LOW);
    buttonHoldCount[button] = 0;
  }
  buttonState[button] = 0;
  deESD[button] = 0;
}

void addPush(int button, int force){
  deESD[button] += 1;
  if(deESD[button] > ESD_COUNT){
    if(force){
      Joystick.setButton(buttonSet[button], HIGH);
      buttonState[button] = 1;      
    } else if(buttonState[button] == 0){
      if(buttonHoldTime[button] == BUTTON_INST){
        Joystick.setButton(buttonSet[button], HIGH);
        buttonState[button] = 1;
      }else if(buttonHoldTime[button] - buttonHoldCount[button] <= 0){
        Joystick.setButton(buttonHoldMap[button], HIGH);
        buttonState[button] = 1;
      } else {
        buttonHoldCount[button] += 1;
      }
    }
  }
}
