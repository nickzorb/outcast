#include <Arduino.h>
#include <Adafruit_MCP23X17.h>
#include "pins.h"

Adafruit_MCP23X17 relayControls[RELAY_CONTROLS];

void setupControls() {
  Wire.begin();
  Wire.setClock(400000);
  for (byte i = 0; i < RELAY_CONTROLS; i++) {
    relayControls[i].begin_I2C(RELAY_ADDRESS + i);
    for (byte j = 0; j < RELAYS_PER_CONTROL; j++) {
      relayControls[i].pinMode(j, OUTPUT);
      relayControls[i].digitalWrite(j, HIGH);
    }
  }
}

void setupInputs() {
  for (byte i = 2; i <= A15; i++) {
    if (i == 20 || i == 21) continue;
    pinMode(i, INPUT_PULLUP);
  }
}

void setMcpPin(byte logicalPin, bool high) {
  byte chip = logicalPin / RELAYS_PER_CONTROL;
  byte pin  = logicalPin % RELAYS_PER_CONTROL;
  if (chip >= RELAY_CONTROLS) return;

  relayControls[chip].digitalWrite(pin, high ? HIGH : LOW);
}

void setRelay(byte id, bool on) {
  setMcpPin(id, !on);
}

void setMagnet(byte id, bool on) {
  setRelay(id, !on);
}
