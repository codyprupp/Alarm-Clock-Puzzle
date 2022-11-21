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

// Define Button Pins and Buzzer Pin
#define MINUTE_ADD_PIN 5
#define MINUTE_SUB_PIN 4
#define HOUR_ADD_PIN 6
#define HOUR_SUB_PIN 7
#define ALARM_SET_PIN 8
#define CLOCK_SET_PIN 9
#define BUZZER_PIN 2

// Create a new instance of the MD_Parola class with hardware SPI connection:
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// Variables for time-keeping
// Setup for software SPI:
// #define DATAPIN 2
// #define CLK_PIN 4
// MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

bool intensity = HIGH;
bool alarmIsSet = false;

long randNum;

unsigned long currTime;

// replace w/ random number for random size generation
int numButtonsToPress = random(8, 12);
int pressOrder[12];

unsigned long previousMillis = 0UL;
unsigned long interval = 1000UL;
int seconds = 0;
int minutes = 0;
int hours = 0;
String minString = String();
String hourString = String();
String timeString = String();

// Variables to manipulate when setting Clock and Alarm
int tempMinutes = 0;
int tempHours = 0;
String tempMinString = String(tempMinutes);
String tempHourString = String(tempHours);
String tempTimeString = String("00:00");
enum selection = {MIN, HOUR};

// Variables to keep track of set Alarm
int alarmMinutes = 0;
int alarmHours = 0;
bool alarmIsSet = false;

// Variables for Game progression
int currColor = 0;
int index = 0;

// Sets up system to keep track of the mode
enum mode {ALARM_SET, CLOCK_SET, CLOCK, GAME};
int currMode = CLOCK;

// Initialize button objects
Button minuteAddButton(MINUTE_ADD_PIN);
Button minuteSubButton(MINUTE_SUB_PIN);
Button clockSetButton(CLOCK_SET_PIN);
Button hourAddButton(HOUR_ADD_PIN);
Button hourSubButton(HOUR_SUB_PIN);
Button alarmSetButton(ALARM_SET_PIN);

// Updates seconds, minutes, and hours in clock format
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

// Updates the Time String for the Display
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

// Updates the Temp Time String for Setting Alarm and Clock
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

// Increments minutes or hours based on received parameter
void increment(int num) {
  switch (num) {
    case MIN:
      tempMinutes++;
      if (tempMinutes > 59) {
        tempMinutes = 0;
      }
      break;
    case HOUR:
      tempHours++;
      if (tempHours > 23) {
        tempHours = 0;
      }
      break;
  }
}

// Decrements minutes or hours based on received parameter
void decrement(int num) {
  switch (num) {
    case MIN:
      tempMinutes--;
      if (tempMinutes < 0) {
        tempMinutes = 59;
      }
      break;
    case HOUR:
      tempHours--;
      if (tempHours < 0) {
        tempHours = 23;
      }
      break;
  }
}

// void incrementMinutes() {
//   tempMinutes++;
//   if (tempMinutes > 59) {
//     tempMinutes = 0;
//   }
// }

// void decrementMinutes() {
//   tempMinutes--;
//   if (tempMinutes < 0) {
//     tempMinutes = 59;
//   }
// }

// void incrementHours() {
//   tempHours++;
//   if (tempHours > 23) {
//     tempHours = 0;
//   }
// }

// void decrementHours() {
//   tempHours--;
//   if (tempHours < 0) {
//     tempHours = 23;
//   }
// }

void setup() {
  // Intialize the object:
  myDisplay.begin();
  // Set the intensity (brightness) of the display (0-15):
  myDisplay.setIntensity(6);
  // Clear the display:
  myDisplay.displayClear();

  pinMode(BUZZER_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  Serial.println(alarmIsSet);
  myDisplay.setTextAlignment(PA_CENTER);
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > interval) {
    updateTime();
    updateTimeString();
    previousMillis = currentMillis;
//
//    if (currMode == CLOCK_SET) {
//      if (intensity == HIGH) {
//        myDisplay.setIntensity(0);
//        intensity = LOW;
//      } else {
//        myDisplay.setIntensity(15);
//        intensity = HIGH;
//      }
//    } 
//    else if (currMode == ALARM_SET) {
//      if (intensity == HIGH) {
//        myDisplay.setInvert(intensity);
//        intensity = LOW;
//      } else {
//        myDisplay.setInvert(intensity);
//        intensity = HIGH;
//      }
//    }
  }

  switch (currMode) {
    case CLOCK:
      myDisplay.setIntensity(6);
      myDisplay.print(timeString);
      if (clockSetButton.isPressed()) {
        currMode = CLOCK_SET;
        tempMinutes = 0;
        tempHours = 0;
        updateTempString();
      }
      
      if (hours == alarmHours && minutes == alarmMinutes && alarmIsSet) {
        index = 0;
        digitalWrite(BUZZER_PIN, HIGH);
        for (int i = 0; i < numButtonsToPress - 1; i++) {
          pressOrder[i] = random(3);
        }
        currTime = currentMillis;
        currMode = GAME;
      }

      if (alarmSetButton.isPressed()) {
        currMode = ALARM_SET;
        tempMinutes = 0;
        tempHours = 0;
        updateTempString();
      }
      
      break;
    case CLOCK_SET:
      myDisplay.print("C" + tempTimeString);
      if (clockSetButton.isPressed()) {
        currMode = CLOCK;
        minutes = tempMinutes;
        hours = tempHours;
        seconds = 0;
        updateTimeString();
      }
      if (minuteAddButton.isPressed()) {
        increment(MIN);
        updateTempString();
      }
      if (minuteSubButton.isPressed()) {
        decrement(MIN);
        updateTempString();
      }

      if (hourAddButton.isPressed()) {
        increment(HOUR);
        updateTempString();
      }

      if (hourSubButton.isPressed()) {
        decrement(HOUR);
        updateTempString();
      }

      if (alarmSetButton.isPressed()) {
        currMode = CLOCK;
      }
      
      break;
    case ALARM_SET:
      myDisplay.print("A" + tempTimeString);
      if (alarmSetButton.isPressed()) {
        alarmMinutes = tempMinutes;
        alarmHours = tempHours;
        alarmIsSet = true;
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

      if (hourAddButton.isPressed()) {
        incrementHours();
        updateTempString();
      }

      if (hourSubButton.isPressed()) {
        decrementHours();
        updateTempString();
      }

      if (clockSetButton.isPressed()) {
        currMode = CLOCK;
      }

      break;
    case GAME:

      enum buttonColors {RED, BLACK, YELLOW, BLUE};

      currColor = pressOrder[index];

      if (index > numButtonsToPress - 1) {
        Serial.println("in game");
        alarmIsSet = false;
        digitalWrite(BUZZER_PIN, LOW);
        numButtonsToPress = random(4, 8);
        currMode = CLOCK;
        break;
      }

      if (currColor == 0) {
        if (currentMillis - currTime < 250) {
          myDisplay.displayClear();
        } else {
          myDisplay.print("Red");
        }
        if (hourSubButton.isPressed()) {
          index++;
          currColor = pressOrder[index];
          currTime = currentMillis;
        }
      } else if (currColor == 1) {
        if (currentMillis - currTime < 250) {
          myDisplay.displayClear();
        } else {
          myDisplay.print("Black");
        }
        if (hourAddButton.isPressed()) {
          index++;
          currColor = pressOrder[index];
          currTime = currentMillis;
        }
      } else if (currColor == 2) {
        if (currentMillis - currTime < 250) {
          myDisplay.displayClear();
        } else {
          myDisplay.print("Yellow");
        }
        if (minuteSubButton.isPressed()) {
          index++;
          currColor = pressOrder[index];
          currTime = currentMillis;
        }
      } else if (currColor == 3) {
        if (currentMillis - currTime < 250) {
          myDisplay.displayClear();
        } else {
          myDisplay.print("Blue");
        }
        if (minuteAddButton.isPressed()) {
          index++;
          currColor = pressOrder[index];
          currTime = currentMillis;
        }
      }

      break;
  }
}
