#pragma once
#include <Arduino.h>
#include "pins.h"

enum EffectType : byte {
  EFFECT_RELAY = 0,
  EFFECT_LIGHT = 1,
  EFFECT_SOUND = 2
};

void updateTimedEffects(const unsigned long now);

void startTimedRelay(const byte id, const bool on, const unsigned long time);
void startTimedLight(const byte id, const bool on, const unsigned long time);
void startTimedSound(const byte id, const byte optCode, const unsigned long time);
