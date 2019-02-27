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
#define DEBOUNCE_LEN 2

#define SAMPLE_PER_LOOP 4

#define ENCODER_COOLDOWN 15
#define ENCODER_FLIP_TIME 235
#define ENCODER_DEBOUNCE_TIME 80
#define ENCODER_FLIP_DEBOUNCE 25

//Inputs pins used for buttons
int buttonSet[] = {
  0, 1, 2, 3, 4,
  5, 6, 7, 8, 9,
  10, 14, 16, 18, 19
};

int buttonState[NUM_BUTTONS];
int deESD[NUM_BUTTONS];
int debounce[NUM_BUTTONS];
int loopState = 0;

int lastRot = -1;
int encoderDirection = -1;
int encWait = 0;
int encFlipWait = 0;

//Rotary inputs, only one supported atm
//For non-interruptable pins
int rotarySet[] = {
  20, 21
};

int rotaryState[2];

int encThisState[2];
int encLastState[2];

int encoderWaiting = true;
int lastDirection = -1;

//Output for rotaries
int rotaryDestButton[] = {
  29, 30
};

//List of pins used to provide high signal
int powerSet[] = {
  15
};

void setup() {
  int i = 0;
  for( i = 0; i < NUM_BUTTONS; i++){
    pinMode(buttonSet[i], INPUT_PULLUP);
    deESD[i] = 0;
    debounce[i] = 0;
    buttonState[i] = 0;
  }
  for( i = 0; i < NUM_ROTARY * 2; i++){
    pinMode(rotarySet[i], INPUT_PULLUP);
    encThisState[i] = encLastState[i] = digitalRead(rotarySet[i]);

  }
  for( i= 0; i < NUM_POWER; i++){
    pinMode(powerSet[i], OUTPUT);
    digitalWrite(powerSet[i], HIGH);
  }

  Joystick.begin();
}



void loop() {
  for( int i = loopState; i <= loopState + SAMPLE_PER_LOOP && i < NUM_BUTTONS; i++){
    int state = digitalRead(buttonSet[i]);
    if (state == LOW && checkDebounce(i)){
      addPush(i);
    } else if (state == HIGH){
      remPush(i);
    }
  }

  //Test non-interupt pins
  encThisState[0] = digitalRead(rotarySet[0]);
  encThisState[1] = digitalRead(rotarySet[1]);

  if ( (encThisState[0] != encLastState[0] || encThisState[1] != encLastState[1]) && encWait == 0 && encoderDirection == -1){
    int noSet = 0;
    if (encThisState[0] != encLastState[0] && encThisState[1] == encLastState[1]){
      encoderDirection = 1;
    } else if (encThisState[0] == encLastState[0] && encThisState[1] != encLastState[1]){
      encoderDirection = 2;
    } else {
      noSet = 1;
      encWait = 1;
    }
    if(noSet == 0){
      if (encFlipWait == 0){
        encFlipWait = 1;
        lastDirection = encoderDirection;
      } else if (encFlipWait < ENCODER_FLIP_TIME){
         encoderDirection = lastDirection; //ignore direction change unless beyond flip window
         delay(ENCODER_FLIP_DEBOUNCE);
      }
      encWait = 1;
    }

  } else if (encWait <= ENCODER_COOLDOWN && encWait > 0) {
    encWait += 1;
    if (encWait >= ENCODER_COOLDOWN){
      encoderDirection = -1;
      encWait = 0;
    }
  }

  if (encFlipWait){
    encFlipWait +=1 ;
    if (encFlipWait > ENCODER_FLIP_TIME){
      encFlipWait = 0;
      lastDirection = -1; //new!

    }
  }

  if(encoderDirection == 1 ){
    if(rotaryState[0] == 0){
      rotaryState[0] = 1;
      rotaryState[1] = 0;
      Joystick.setButton(rotaryDestButton[0],HIGH);
      Joystick.setButton(rotaryDestButton[1],LOW);
      delay(ENCODER_DEBOUNCE_TIME);
    }
  } else if  (encoderDirection == 2){
    if(rotaryState[1] == 0){
      rotaryState[0] = 0;
      rotaryState[1] = 1;
      Joystick.setButton(rotaryDestButton[0],LOW);
      Joystick.setButton(rotaryDestButton[1],HIGH);
      delay(ENCODER_DEBOUNCE_TIME);
    }

  } else {
    if(rotaryState[0] == 1){
      rotaryState[0] = 0;
      Joystick.setButton(rotaryDestButton[0],LOW);
      delay(ENCODER_DEBOUNCE_TIME);
    }
    if(rotaryState[1] == 1){
      rotaryState[1] = 0;
      Joystick.setButton(rotaryDestButton[1],LOW);
      delay(ENCODER_DEBOUNCE_TIME);
    }

  }


  loopState += SAMPLE_PER_LOOP;
  if (loopState >= NUM_BUTTONS)
    loopState = 0;

  encLastState[0] = encThisState[0];
  encLastState[1] = encThisState[1];
}


void remPush(int button){
  if (buttonState[button] == 1){
    Joystick.setButton(buttonSet[button], LOW);
  }
  buttonState[button] = 0;
  deESD[button] = 0;
}

void addPush(int button){
  deESD[button] += 1;
  if(deESD[button] > ESD_COUNT){
    if(buttonState[button] == 0){
     Joystick.setButton(buttonSet[button], HIGH);
    }
    debounce[button] = DEBOUNCE_LEN;
    buttonState[button] = 1;
  }
}

//Return true button is available to push
int checkDebounce(int button){
  if (debounce[button] <= 0){
    debounce[button] = 0;
    return 1;
  } else {
    debounce[button] -= 1;
  }
  return 0;
}
