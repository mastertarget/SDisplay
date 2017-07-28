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
SOFTWARE.*/
#ifndef __SDISPLAY_H
#define __SDISPLAY_H
/*
** 7-segment-display library
** SDisplay.h
** v0.0.1
** Chris Goertz
** 2017-07-24
** this library is usable for latched 7-segment-displays
** my displays are driven by 74hc564 inverted octal latches
** and uln2004 darlington drivers
** tested on Arduino UNO ATMega328P
*/
/*
**2017-07-25 v.0.0.1
**2017-07-27 code clean up
*/

/*
** include libraries
*/
#include <Arduino.h>
/*
** Makros etc
*/
#define COM_ANODE true
#define COM_CATHODE false
#define FLIPPED true
#define NOT_FLIPPED false
#define SEGA 0
#define SEGB 1
#define SEGC 2
#define SEGD 3
#define SEGE 4
#define SEGF 5
#define SEGG 6
#define SEGMENT_COUNT 7
#define ONBOARD_LED 13
#define MAX_DISPLAY_VALUE 9 //DECIMAL VALUES ONLY

/*
**7-segment-display class
*/
class SDisplay{
  /*
  **private variables and methods
  */
  private:
    uint8_t segmente[7] = {}; //the led pins
    uint8_t latch = 0;        //the latch pin
    bool isFlipped = false;   // for 180 degr flipped mode
    bool displayType = true;  // specify the display type
    const uint8_t bitmask[2][10] = {{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f},
                                    {0x3f,0x30,0x5b,0x79,0x74,0x6d,0x6f,0x38,0x7f,0x7d}};
    /*
    **initialize pin directions
    */
    void _init(void);
    /*
    **latch the new state
    */
    void _update(void);
    /**
    **public methods
    */
  public:
    /*
    **Constructor
    **define the pins of the 7-segment-display
    */
    SDisplay( uint8_t segAPin, uint8_t segBPin,
              uint8_t segCPin, uint8_t segDPin,
              uint8_t segEPin, uint8_t segFPin,
              uint8_t segGPin, uint8_t latchPin,
              bool dispType);
    /*
    **set DisplayType common anode or common cathode
    **parameters COM_ANODE | COM_CATHODE
    */
    void setDisplayType(bool type);
    /*
    **set orientation of the display
    **if enabled, the display shows
    **numbers 180 degrees FLIPPED
    **parameters FLIPPED | NOT_FLIPPED
    */
    void setOrientation(bool mode);
    /*
    **display the decimal number on the digit
    **parameter 0...9
    */
    void num(uint8_t number);
    /*
    **clear digit eg switch off
    */
    void clear(void);
    /*
    **test segements
    */
    void lampTest(void);
};

#endif
