#include "LedControl.h"


#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 3
#define DIN_PIN 11
#define CLK_PIN 13

LedControl lc=LedControl(DIN_PIN,CLK_PIN,CS_PIN,MAX_DEVICES);

int currDisplay = 0;

void setup() {
  lc.shutdown(0,false);  // Wake up displays
  lc.shutdown(1,false);
  lc.shutdown(2,false);
  lc.shutdown(3,false);
  lc.setIntensity(0,5);  // Set intensity levels
  lc.setIntensity(1,5);
  lc.setIntensity(2,5);
  lc.setIntensity(3,5);
  lc.clearDisplay(0);  // Clear Displays
  lc.clearDisplay(1);
  lc.clearDisplay(2);
  lc.clearDisplay(3);
  Serial.begin(2000000);
}

void displayLeft(int currDisplay) {
  lc.clearDisplay(currDisplay);
  lc.setRow(currDisplay,0,B11111111);
  lc.setColumn(currDisplay,0,B11111111);
  lc.setColumn(currDisplay,7,B11111111);
  lc.setRow(currDisplay,7,B11111111);
}

void displayRight(int currDisplay) {
  lc.clearDisplay(currDisplay);
  lc.setRow(currDisplay-1,0,B11111111);
  lc.setColumn(currDisplay-1,0,B11111111);
  lc.setColumn(currDisplay-1,7,B11111111);
  lc.setRow(currDisplay-1,7,B11111111);
}

void loop() {
  // put your main code here, to run repeatedly:
//  lc.setLed(0,0,0,true);
//  lc.setLed(1,1,1,true);
//  lc.setLed(2,2,2,true);
//  lc.setLed(3,3,3,true);

  lc.setRow(currDisplay,0,B11111111);
  lc.setColumn(currDisplay,0,B11111111);
  lc.setColumn(currDisplay,7,B11111111);
  lc.setRow(currDisplay,7,B11111111);


  char input = Serial.readString()[0];
  if (input == 'a') {
    lc.clearDisplay(currDisplay);
    currDisplay++;
  } else if (input == 'd') {
    Serial.println("clearing display!");
    lc.clearDisplay(currDisplay);
    currDisplay--;
  }
//  while (Serial.available() == 0) {
//    Serial.println(input);
//    if (input == 'a') {
//      lc.clearDisplay(currDisplay);
//      currDisplay++;
//    } else if (input = 'd') {
//      currDisplay--;
//    } else {
//      
//    }
//     switch (input) {
//      case 'a':
//        lc.clearDisplay(currDisplay);
//        currDisplay++;
//        break;
//      case 'd':
//        lc.clearDisplay(currDisplay);
//        currDisplay--;
//        break;
//     }
//     input = ' ';
//  }

  // on left arrow key press, increment displayAddress by 1 and clear all other displays
  // on right arrow key press, decrement displayAddress by 1
}
