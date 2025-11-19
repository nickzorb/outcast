#include <Arduino.h>
#include "sounds.h"

void playSound(byte opcode, byte id) {
  Serial.write((opcode << 5) | id);
  Serial.flush();
}
