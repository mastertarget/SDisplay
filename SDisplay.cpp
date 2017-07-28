/*MIT License

Copyright (c) 2017 Christian Goertz

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
/*
** 7-segment-display library
** SDisplay.cpp
** v0.0.1
** Chris Goertz
** 2017-07-24
*/

#include <Arduino.h>
#include <SDisplay.h>


void SDisplay::_init(void){
  pinMode(ONBOARD_LED,OUTPUT); //Diagnostics
  //Initialize MCU pins as OUTPUT
  for(uint8_t i = 0; i<7; i++){
    pinMode(this->segmente[i],OUTPUT);
    digitalWrite(this->segmente[i],this->displayType);
    pinMode(this->latch,OUTPUT);
    digitalWrite(this->latch,LOW);

  }
}
void SDisplay::_update(){
  digitalWrite(this->latch,HIGH);
  delay(1);
  digitalWrite(this->latch,LOW);
}
/*
**Constructor
*/
SDisplay::SDisplay(uint8_t segAPin, uint8_t segBPin,
          uint8_t segCPin, uint8_t segDPin,
          uint8_t segEPin, uint8_t segFPin,
          uint8_t segGPin, uint8_t latchPin,
          bool dispType){
  this->latch = latchPin;
  this->segmente[SEGA] = segAPin;
  this->segmente[SEGB] = segBPin;
  this->segmente[SEGC] = segCPin;
  this->segmente[SEGD] = segDPin;
  this->segmente[SEGE] = segEPin;
  this->segmente[SEGF] = segFPin;
  this->segmente[SEGG] = segGPin;
  this->displayType = dispType;
  this->_init();
}

/*
**
*/
void SDisplay::setDisplayType(bool type){
  this->displayType = type;
}
void SDisplay::setOrientation(bool mode){
  this->isFlipped = mode;
}
void SDisplay::num(uint8_t number){
  static uint8_t oldValue = 0;
  //useless update prevention
  if (oldValue == number){
    return;
  }
  if(number > MAX_DISPLAY_VALUE){
    //if value is to high, show nothing but LED13
    this->clear();
    digitalWrite(ONBOARD_LED,HIGH);
    return;
  }
  uint8_t flipped = 0;
  if(this->isFlipped){
    flipped = 1;
  }
  for(uint8_t i = 0; i<7; i++){
    if(this->displayType){
      digitalWrite(this->segmente[i],(~(this->bitmask[flipped][number]) >> i)&0x01);
    }
    else{
      digitalWrite(this->segmente[i],((this->bitmask[flipped][number]) >> i)&0x01);
    }
  }
  oldValue = number;
  this->_update();
}
void SDisplay::clear(void){
  //active low if common anode display is used
  for(uint8_t i = 0; i < SEGMENT_COUNT; i++){
    digitalWrite(i,!this->displayType);

  }
  this->_update();
}
void SDisplay::lampTest(void){
  //active if common anode display is used
  for(uint8_t i = 0; i < SEGMENT_COUNT; i++){
    digitalWrite(i,this->displayType);
  }
  this->_update();
}
