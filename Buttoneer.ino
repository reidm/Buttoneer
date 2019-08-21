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


//#include <digitalWriteFast.h>
#include "Arduino.h"
//#include <EnableInterrupt.h>
#include "src/interfaces/SensorInterface.h"
#include "src/Encoder.h"
#include "src/ControllerState.h"
#include "Buttoneer.h"

//#include "src/IOPoller.h"

#include "config/ButtoneerConfig.h"

EncoderInterface* encInt[ENCODER_NUM];
volatile Encoder* enc[ENCODER_NUM];
volatile ControllerState* cs;


void setup() {
  Serial.begin(9600);
  delay(2500);
  Serial.println("FRESHBOOT");
  cs = new ControllerState();
  //cs->setupEncoders(ENCODER_0+ENCODER_1+ENCODER_2+ENCODER_3+ENCODER_4);
  cs->createButtons();
  #if(ENCODER_4 == ON)
    Serial.println("ENCODER_4B SETUP ON PINS 10 & 16");
    encInt[4] = new EncoderInterface();
    encInt[4]->pinL = ENCODER_4_PIN_L;
    encInt[4]->pinR = ENCODER_4_PIN_R;
    encInt[4]->buttonMapL = ENCODER_4_BUTTON_L;
    encInt[4]->buttonMapR = ENCODER_4_BUTTON_R;
    enc[4] = new Encoder();
    enc[4]->setup(encInt[4]);
    //enableInterrupt(ENCODER_4_PIN_L, handleEncoderInterrupt4, CHANGE);
    //enableInterrupt(ENCODER_4_PIN_R, handleEncoderInterrupt4, CHANGE);
    enc[4]->addSubscriber(cs);
  #endif
}

void loop() {
  cs->handleEVQ();
}

void handleEncoderInterrupt4(){
  enc[4]->handleInterrupt();
}

void interruptButton0(){
  Serial.println("Global handle button 0");
  cs->passButtonInterrupt(0);
}

void interruptButton1(){
  Serial.println("Global handle button 1");
  cs->passButtonInterrupt(1);
}
