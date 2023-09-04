#include "Button.h"


Button::Button(int8_t pin)  {
  this->pin = pin;
  pinMode(pin, INPUT);
}

uint8_t Button::get(){
  return digitalRead(this->pin);
}
