
#include <SDisplay.h>

#define SEG_A_PIN 3
#define SEG_B_PIN 4
#define SEG_C_PIN 5
#define SEG_D_PIN 6
#define SEG_E_PIN 7
#define SEG_F_PIN 8
#define SEG_G_PIN 9
#define LATCH_DIGIT1 A0
#define LATCH_DIGIT2 A1
#define LATCH_DIGIT3 A2
#define LATCH_DIGIT4 A3
#define DIGIT_COUNT 4
#define BAUD_RATE 9600

//SDisplay objects
//Digit 1 minutes lower digit
SDisplay Digit1(SEG_A_PIN, SEG_B_PIN,
                SEG_C_PIN, SEG_D_PIN,
                SEG_E_PIN, SEG_F_PIN,
                SEG_G_PIN, LATCH_DIGIT1, COM_ANODE);
//Digit 2 minutes upper digit
SDisplay Digit2(SEG_A_PIN, SEG_B_PIN,
                SEG_C_PIN, SEG_D_PIN,
                SEG_E_PIN, SEG_F_PIN,
                SEG_G_PIN, LATCH_DIGIT2, COM_ANODE);
//Digit 3 hours lower digit
SDisplay Digit3(SEG_A_PIN, SEG_B_PIN,
                SEG_C_PIN, SEG_D_PIN,
                SEG_E_PIN, SEG_F_PIN,
                SEG_G_PIN, LATCH_DIGIT3, COM_ANODE);
//Digit 4 hours upper digit
SDisplay Digit4(SEG_A_PIN, SEG_B_PIN,
                SEG_C_PIN, SEG_D_PIN,
                SEG_E_PIN, SEG_F_PIN,
                SEG_G_PIN, LATCH_DIGIT4, COM_ANODE);
//array of digits for fast iterate
SDisplay *digits[DIGIT_COUNT] = {&Digit1,&Digit2,&Digit3,&Digit4};
//uptime in seconds
long uptime = 0;

void setup(){
  //use Serial
  Serial.begin(BAUD_RATE);
  //clear digits and set orientation
  for(uint8_t i = 0; i<DIGIT_COUNT;i++){
    digits[i]->clear();
    digits[i]->setOrientation(NOT_FLIPPED);
  }
  //display digits position on each digit
  for(uint8_t i = 0; i<DIGIT_COUNT;i++){
    digits[i].num(i);
  }
}

void loop(){
  //print every second the uptime
  if((millis() - uptime) >1000){
    Serial.println(millis()/1000);
    uptime = millis();
  }

}
