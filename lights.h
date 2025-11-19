#pragma once
#include <Arduino.h>

extern const byte LIGHT_SOURCES[];
extern const byte LIGHT_REVERSED[];
extern const byte LIGHT_COUNT;

void setupLights();
void setLight(byte id, bool on);
void doBlackout();
