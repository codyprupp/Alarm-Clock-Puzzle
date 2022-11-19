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
#define leftButtonPin 4
#define rightButtonPin 5
#define upButtonPin 6
#define downButtonPin 7
#define alarmButtonPin 8
#define clockButtonPin 9

// Create a new instance of the MD_Parola class with hardware SPI connection:
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// Setup for software SPI:
// #define DATAPIN 2
// #define CLK_PIN 4
// MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

unsigned long previousMillis = 0UL;
unsigned long interval = 1000UL;
int seconds = 0;
int minutes = 0;
int hours = 0;
String secString = String();
String minString = String();
String timeString = String();

enum mode {ALARM_SET, CLOCK_SET, CLOCK, GAME};
int currMode = CLOCK;

Button leftButton(leftButtonPin);
Button rightButton(rightButtonPin);


void updateTime() {
  seconds++;
  if (seconds > 59) {
    minutes++;
    seconds = 0;
  }
}

void updateTimeString() {
    secString = String(seconds);
    minString = String(minutes);

    if (seconds < 10) {
      secString = String("0" + secString);
    }
    
    if (minutes < 10) {
      minString = String("0" + minString);
    }
    timeString = String(minString + ":" + secString);
}

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

  if(currentMillis - previousMillis > interval) {
    updateTime();
    updateTimeString();
    previousMillis = currentMillis;
  }

  switch (currMode) {
    case CLOCK:
      myDisplay.print(timeString);
      if(leftButton.isPressed()) {
        currMode = CLOCK_SET;
      }
      break;
    case CLOCK_SET:
      myDisplay.print("SET");
      if(leftButton.isPressed()) {
        currMode = CLOCK;
      }
      break;
  }
  
}