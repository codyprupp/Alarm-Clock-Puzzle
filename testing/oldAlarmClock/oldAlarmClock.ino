/* Basic example code for MAX7219 LED dot matrix display with Arduino. More info: https://www.makerguides.com */

// Include the required Arduino libraries:
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include "button.h"

// Define hardware type, size, and output pins:
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 3
#define DIN_PIN 11
#define CLK_PIN 13
#define LEFT_BUTTON_PIN 4
#define RIGHT_BUTTON_PIN 5
#define UP_BUTTON_PIN 6
#define DOWN_BUTTON_PIN 7
#define A_BUTTON_PIN 8 // also alarm button
#define B_BUTTON_PIN 9 //also clock button

// Create a new instance of the MD_Parola class with hardware SPI connection:
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// Setup for software SPI:
// #define DATAPIN 2
// #define CLK_PIN 4
// MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

Button leftButton(LEFT_BUTTON_PIN);
Button rightButton(RIGHT_BUTTON_PIN);
Button upButton(UP_BUTTON_PIN);
Button downButton(DOWN_BUTTON_PIN);
Button aButton(A_BUTTON_PIN);
Button bButton(B_BUTTON_PIN);

unsigned long previousMillis = 0UL;
unsigned long interval = 1000UL;
int seconds = 40;
int minutes = 2;
int hours = 0;

enum mode {ALARM_SET, CLOCK_SET, CLOCK, GAME};
int currMode = CLOCK;

void setup() {
  // Intialize the object:
  myDisplay.begin();
  // Set the intensity (brightness) of the display (0-15):
  myDisplay.setIntensity(6);
  // Clear the display:
  myDisplay.displayClear();
  Serial.begin(9600);
}

void loop() {
  myDisplay.setTextAlignment(PA_CENTER);
  unsigned long currentMillis = millis();

  String secString = String(seconds);
  String minString = String(minutes);

  if(currentMillis - previousMillis > interval)
  {
    seconds++;
    if (seconds > 59) {
      minutes++;
      seconds = 0;
    }
    if (minutes > 59) {
      
    }

    previousMillis = currentMillis;
  }
  switch (currMode) {
    case CLOCK:
//        String secString = String(seconds);
//        String minString = String(minutes);

      if (seconds < 10) {
        secString = String("0" + secString);
      }
      
      if (minutes < 10) {
        minString = String("0" + minString);
      }
      String timeString = String(minString + ":" + secString);
      myDisplay.print(timeString);

      Serial.println(currMode);

      if (aButton.isPressed()) {
        currMode = 1;
      } else if (bButton.isPressed()) {
        currMode = 0;
      }
    case 1:
//      myDisplay.print("clock set");
      Serial.println(currMode);
      if (aButton.isPressed()) {
        currMode = 2;
      }
    case ALARM_SET:
//      myDisplay.print("alarm set");
      if (bButton.isPressed()) {
        currMode = 2;
      }
    }
}
