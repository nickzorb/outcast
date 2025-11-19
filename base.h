#pragma once
#include <Arduino.h>

#define SAFETY_REPEATS      5
#define SAFETY_DELAY        100
#define MAX_STAGES          25

extern volatile byte stage;
extern volatile bool bypassed;

bool saferDigitalRead(byte pin);
int saferAnalogRead(byte pin);
