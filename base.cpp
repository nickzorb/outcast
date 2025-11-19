#include <Arduino.h>
#include "base.h"

volatile byte stage = 0;
volatile bool bypassed = false;

bool saferDigitalRead(byte pin) {
  byte res = digitalRead(pin);
  for (byte i = 0; i < SAFETY_REPEATS - 1; i++) {
    delayMicroseconds(SAFETY_DELAY);
    res += digitalRead(pin);
  } 
  return res >= (SAFETY_REPEATS + 1) / 2;
}

int saferAnalogRead(byte pin) {
  analogRead(pin);
  int res = 0;
  for (byte i = 0; i < SAFETY_REPEATS; i++) {
    delayMicroseconds(SAFETY_DELAY);
    res += analogRead(pin);
  } 
  return res / SAFETY_REPEATS;
}