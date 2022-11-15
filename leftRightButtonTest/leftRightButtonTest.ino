#include "LedControl.h"
int leftButtonPin = 12;
int rightButtonPin = 8;


#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 3
#define DIN_PIN 11
#define CLK_PIN 13

LedControl lc=LedControl(DIN_PIN,CLK_PIN,CS_PIN,MAX_DEVICES);

int currDisplay = 0;
bool leftButtonPressed = false;
bool rightButtonPressed = false;

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
  pinMode(leftButtonPin, INPUT_PULLUP);
  pinMode(rightButtonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  int leftButtonValue = digitalRead(leftButtonPin);
  int rightButtonValue = digitalRead(rightButtonPin);
  
  lc.setRow(currDisplay,0,B11111111);
  lc.setColumn(currDisplay,0,B11111111);
  lc.setColumn(currDisplay,7,B11111111);
  lc.setRow(currDisplay,7,B11111111);
  
  if (leftButtonValue == LOW && !leftButtonPressed) {
    Serial.println("left button has been pressed");
    lc.clearDisplay(currDisplay);
    currDisplay++;
    leftButtonPressed = true;
  }

  if (leftButtonValue == HIGH) {
    leftButtonPressed = false;
  }

  if (rightButtonValue == LOW && !rightButtonPressed) {
    Serial.println("right button has been pressed");
    lc.clearDisplay(currDisplay);
    currDisplay--;
    rightButtonPressed = true;
  }

  if (rightButtonValue == HIGH) {
    rightButtonPressed = false;
  }
}
