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
#define ESD_COUNT 5
#define HOLD_DEBOUNCE 10
#define SAMPLE_PER_LOOP 1

#define BUTTON_OFF 0
#define BUTTON_PUSHED 1
#define BUTTON_HELD 2
#define BUTTON_PUSHED_SHORT 3
#define BUTTON_HELD_LONG 4
#define BUTTON_PUSH_THRESH 600
#define BUTTON_PUSH_LENGTH 200
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

#define BUTTON_INST -1
#define BUTTON_HOLD 600

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
int buttonHeld[NUM_BUTTONS];
int deESD[NUM_BUTTONS];

int loopState = 0;
int state;





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
  //for(int i = loopState; i <= loopState + SAMPLE_PER_LOOP && i < NUM_BUTTONS; i++){
  state = digitalRead(BUTTON_SET[loopState]);
  if(state == LOW){
    Serial.println("Button was off");
    if(HOLD_MAP[loopState] == BUTTON_INST){
      if(buttonState[loopState] == BUTTON_OFF){
        Serial.println("insta push");
        addPush(loopState);
      }
    } else {
      holdManage(loopState);
    } 
  } else {//state==HIGH
    if(buttonState[loopState] == BUTTON_PUSHED){
      Serial.println("remPush");
      remPush(loopState);
    } else if(buttonState[loopState] == BUTTON_HELD){
      addShortPush(loopState);
    } else if(buttonState[loopState] == BUTTON_PUSHED_SHORT) {
      if(buttonHoldCount[loopState] >= 1){
        buttonHoldCount[loopState] -= 1;
      }

      Serial.print("button pushed short / ");
      Serial.println(buttonHoldCount[loopState]);
      if(buttonHoldCount[loopState] == 0){
        buttonState[loopState] = BUTTON_OFF;
        Joystick.setButton(BUTTON_SET[loopState], LOW);
      }
    } else if(buttonState[loopState] == BUTTON_HELD_LONG){
      Serial.println("PUSHEDLONG");
      addLongPush(loopState);
    }
    deESD[loopState] = 0;
  }

  loopState += SAMPLE_PER_LOOP;
  if(loopState >= NUM_BUTTONS)
    loopState = 0;
  //encoder code here

}

void addShortPush(int button){
  Serial.println("short push add");
  buttonState[button] = BUTTON_PUSHED_SHORT;
  buttonHoldCount[button] = BUTTON_PUSH_LENGTH;
  Joystick.setButton(BUTTON_SET[button], HIGH);
}

void addLongPush(int button){
  Serial.println("long push add");
  
}
void holdManage(int button){
  buttonHoldCount[button] += 1;
  
  if(buttonHoldCount[button] > HOLD_DEBOUNCE){
    buttonState[button] = BUTTON_HELD;
    Serial.print("Button held / ");
    Serial.println(buttonHoldCount[button]);
    Serial.println(buttonState[button]);
    if(buttonHoldCount[button] > BUTTON_PUSH_THRESH){
      Serial.println("LONGLONGLONG");
      buttonState[button] = BUTTON_HELD_LONG;
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
    Serial.println("release");
    Serial.println(buttonState[button]);
    Joystick.setButton(BUTTON_SET[button], LOW);
    buttonState[button] = BUTTON_OFF;
    deESD[button] = 0;

  } 
}


/* junk
 *  
 *  

  /*
  if(state == LOW && buttonState[loopState] == BUTTON_OFF) { 
    if(HOLD_MAP[loopState] == BUTTON_INST){
      Serial.println("soft push");
      addPush(loopState, false);
    } else {
      Serial.println("hard push");
      addPush(loopState, true);
    }
  }
  else if(state == LOW && buttonState[loopState] == BUTTON_HELD && buttonHoldCount[loopState] >= 0){
    buttonHoldCount[loopState] += 1;
    Serial.println("Still held");
    Serial.println(buttonHoldCount[loopState]);
    if(buttonHoldCount[loopState] >= BUTTON_PUSHED_LONG){
      Serial.println("LONGLONGLONG");
      buttonState[loopState] == BUTTON_OFF;
    }
  } else if(state == HIGH && buttonState[loopState] == BUTTON_HELD){
    Serial.println("Found end of push");
    addPush(loopState, true);
  } else if(state == HIGH && buttonState[loopState] == BUTTON_PUSHED){
  

    remPush(loopState);
  } else {
    deESD[loopState] = 0;
    buttonHoldCount[loopState] = 0;
  }*/
  







/* 
#define ENCODER_HOLD 2000
#define ENCODER_DEBOUNCE 1


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
*/
  /*encoder code goes up there
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
  */
