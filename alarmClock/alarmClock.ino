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
#define MINUTE_ADD_PIN 4
#define MINUTE_SUB_PIN 5
#define HOUR_ADD_PIN 6
#define HOUR_SUB_PIN 7
#define ALARM_SET_PIN 8
#define CLOCK_SET_PIN 9

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
String minString = String();
String hourString = String();
String timeString = String();

int tempMinutes = 0;
int tempHours = 0;
String tempMinString = String(tempMinutes);
String tempHourString = String(tempHours);
String tempTimeString = String("00:00");

enum mode {ALARM_SET, CLOCK_SET, CLOCK, GAME};
int currMode = CLOCK;

Button minuteAddButton(MINUTE_ADD_PIN);
Button minuteSubButton(MINUTE_SUB_PIN);
Button clockSetButton(CLOCK_SET_PIN);


void updateTime() {
  seconds++;
  if (seconds > 59) {
    minutes++;
    seconds = 0;
  }
  if (minutes > 59) {
    hours++;
    minutes = 0;
  }
  if (hours > 23) {
    hours = 0;
  }
}

void updateTimeString() {
  hourString = String(hours);
  minString = String(minutes);

  if (hours < 10) {
    hourString = String("0" + hourString);
  }
  
  if (minutes < 10) {
    minString = String("0" + minString);
  }
  timeString = String(hourString + ":" + minString);
}

void updateTempString() {
  tempMinString = String(tempMinutes);
  tempHourString = String(tempHours);

  if (tempMinutes < 10) {
    tempMinString = String("0" + tempMinString);
  }
  if (tempHours < 10) {
    tempHourString = String("0" + tempHourString);
  }
  tempTimeString = String(tempHourString + ":" + tempMinString);
}

void incrementMinutes() {
  tempMinutes++;
  if (tempMinutes > 59) {
    tempMinutes = 0;
  }
}

void decrementMinutes() {
  tempMinutes--;
  if (tempMinutes < 0) {
    tempMinutes = 59;
  }
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
      if (clockSetButton.isPressed()) {
        currMode = CLOCK_SET;
      }
      break;
    case CLOCK_SET:
      myDisplay.print(tempTimeString);
      if (clockSetButton.isPressed()) {
        currMode = CLOCK;
      }
      if (minuteAddButton.isPressed()) {
        incrementMinutes();
        updateTempString();
      }
      if (minuteSubButton.isPressed()) {
        decrementMinutes();
        updateTempString();
      }

      break;
  }
  
}