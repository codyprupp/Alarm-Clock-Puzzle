#include "button.h"

Button::Button(int pin) {
  this->pin = pin;
  this->state = 0; // not pressed
  pinMode(pin, INPUT_PULLUP);
}

bool Button::isPressed() {
  if (digitalRead(pin) == HIGH) {
    state = 0;
    return false;
  }
  
  if (digitalRead(pin) == LOW && state == 0) {
    state = 1;
    return true;
  } else {
    return false;
  }
}

int Button::getState() {
  return state;
}
