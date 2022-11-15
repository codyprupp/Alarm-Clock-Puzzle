#include "LedControl.h"
#include "button.h"
#define LEFT_BUTTON_PIN 4
#define RIGHT_BUTTON_PIN 5
//#define UP_BUTTON_PIN
//#define DOWN_BUTTON_PIN
//#define A_BUTTON_PIN
//#define B_BUTTON_PIN


#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 3
#define DIN_PIN 11
#define CLK_PIN 13

LedControl lc=LedControl(DIN_PIN,CLK_PIN,CS_PIN,MAX_DEVICES);

int currDisplay = 0;

Button leftButton(LEFT_BUTTON_PIN);
Button rightButton(RIGHT_BUTTON_PIN);

void setup() {
  for (int i = 0; i <= 3; i++) {
    lc.shutdown(i, false); // wake up display
    lc.setIntensity(i, 5);
    lc.clearDisplay(i);
  }
  
  Serial.begin(9600);
}

void loop() {  
  lc.setRow(currDisplay,0,B11111111);
  lc.setColumn(currDisplay,0,B11111111);
  lc.setColumn(currDisplay,7,B11111111);
  lc.setRow(currDisplay,7,B11111111);

  Serial.println(leftButton.getState());
  Serial.println(digitalRead(LEFT_BUTTON_PIN));
  
  if (leftButton.isPressed()) {
    Serial.println("left button has been pressed");
    lc.clearDisplay(currDisplay);
    currDisplay++;
  }

  if (rightButton.isPressed()) {
    Serial.println("right button has been pressed");
    lc.clearDisplay(currDisplay);
    currDisplay--;
  }
}
