#include <Arduino.h>
#include "lights.h"
#include "pins.h"

const byte LIGHT_SOURCES[] = {
  LED_STORAGE,
  LED_GAS_ROOM,
  LED_CORRIDOR_A,
  LED_CORRIDOR_B,
  LED_CORRIDOR_C,
  LED_ELEVATOR_SPOT,
  LED_ELEVATOR_LED,
  LED_CORRIDOR_RED,
  LED_CORRIDOR_WH,
  LED_BED_MAIN,
  LED_ULTRA_SPOT_A,
  LED_ULTRA_SPOT_B,
  LED_ULTRA_SPOT_C,
  LED_ULTRA_SPOT_D,
  LED_ULTRA_SPOT_E,
  LED_ULTRA_SPOT_F,
  LED_ULTRA_LED_A,
  LED_ULTRA_LED_B,
  LED_ULTRA_LED_C,
  LED_ULTRA_LED_D,
  LED_ULTRA_LED_E,
  LED_ULTRA_LED_F,
  LED_FRIDGE,
  LED_WC,
  LED_OFFICE,
  LED_FANS,
  LED_CELL_1,
  LED_CELL_2,
  LED_TUNNEL,
  LED_MONEY_LAMP,
  LED_FINALE,
  LED_SIREN,
  LED_PAD_CORRIDOR,
  LED_PAD_BED,
  LED_CLOCK,
  LED_OVEN,
  LED_ELEVATOR_A,
  LED_ELEVATOR_B,
  LED_ELEVATOR_C,
  LED_ELEVATOR_D,
  LED_ELEVATOR_E,
  LED_ELEVATOR_F,
  LED_ELEVATOR_G,
  POW_ULTRASOUND_B,
  LED_FLY_CATCHER
};

const byte LIGHT_REVERSED[] = {
  1, 1, 1, 1, 1, 1, 0, 1, 0, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1
};

const byte LIGHT_COUNT = sizeof(LIGHT_SOURCES) / sizeof(LIGHT_SOURCES[0]);

bool inBlackout = false;
byte lightStates[LIGHT_COUNT];
byte storedLightStates[LIGHT_COUNT];

void setupLights() {
  for (byte i = 0; i < LIGHT_COUNT; i++) {
    lightStates[i] = LIGHT_REVERSED[i];
    storedLightStates[i] = lightStates[i];
  }
}

byte findLightIndex(byte logicalPin) {
  for (byte i = 0; i < LIGHT_COUNT; i++) {
    if (LIGHT_SOURCES[i] == logicalPin) {
      return i;
    }
  }
  return 255;
}

void applyLightState(byte idx, bool on) {
  byte pin = LIGHT_SOURCES[idx];
  setRelay(pin, LIGHT_REVERSED[idx] ? !on : on);
}

void setLight(byte id, bool on) {
  byte idx = findLightIndex(id);
  if (idx >= LIGHT_COUNT) {
    return;
  }
  if (inBlackout) {
    storedLightStates[idx] = on;
  } else {
    lightStates[idx] = on;
    applyLightState(idx, on);
  }
}

void applyAllLightsFromState() {
  for (byte i = 0; i < LIGHT_COUNT; i++) {
    applyLightState(i, lightStates[i]);
    delay(1);
  }
}

void doBlackout() {
  inBlackout = !inBlackout;
  if (inBlackout) {
    for (byte i = 0; i < LIGHT_COUNT; i++) {
      storedLightStates[i] = lightStates[i];
      lightStates[i] = OFF;
    }
  } else {
    for (byte i = 0; i < LIGHT_COUNT; i++) {
      lightStates[i] = storedLightStates[i];
    }
  }
  applyAllLightsFromState();
}
