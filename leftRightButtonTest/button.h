#ifndef button_h
#define button_h

#include <Arduino.h>

class Button {
  private:
    int pin;
    bool state; // will be 1 while the button is pressed/held; 0 otherwise

  public:
    //public vars
    Button(int pin);
    bool isPressed(); //idk if this will work correctly b/c it's a built-in function
};

#endif
