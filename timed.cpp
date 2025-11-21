#include <Arduino.h>
#include "timed.h"
#include "lights.h"
#include "sounds.h"
#include "pins.h"
#include "base.h"

struct TimedEffect {
  bool active;
  EffectType type;
  byte id;
  byte optCode;
  unsigned long time;
};

constexpr byte MAX_EFFECTS = 100;
static TimedEffect effects[MAX_EFFECTS];

static byte findFreeSlot() {
  for (byte i = 0; i < MAX_EFFECTS; i++) {
    if (!effects[i].active) return i;
  }
  return 0;
}

void updateTimedEffects(const unsigned long now) {
  for (byte i = 0; i < MAX_EFFECTS; i++) {
    if (!effects[i].active) continue;
    if (now >= effects[i].time) {
      switch (effects[i].type) {
        case EFFECT_RELAY:
          setRelay(effects[i].id, effects[i].optCode);
          break;
        case EFFECT_LIGHT:
          setLight(effects[i].id, effects[i].optCode);
          break;
        case EFFECT_SOUND:
          playSound(effects[i].optCode, effects[i].id);
          break;
        case EFFECT_STAGE:
          stage++;
          break;
      }
      effects[i].active = false;
    }
  }
}

void startTimedEvent(const byte id, const byte optCode, const unsigned long time, const EffectType type) {
  byte slot = findFreeSlot();
  
  effects[slot].active = true;
  effects[slot].type = type;
  effects[slot].id = id;
  effects[slot].optCode = optCode;
  effects[slot].time = time;
}

void startTimedRelay(const byte id, const bool on, const unsigned long time) {
  startTimedEvent(id, on, time, EFFECT_RELAY);
}

void startTimedMagnet(const byte id, const bool on, const unsigned long time) {
  startTimedRelay(id, !on, time);
}

void startTimedLight(const byte id, const bool on, const unsigned long time) {
  startTimedEvent(id, on, time, EFFECT_LIGHT);
}

void startTimedSound(const byte id, const byte optCode, const unsigned long time) {
  startTimedEvent(id, optCode, time, EFFECT_SOUND);
}

void startTimedStage(const unsigned long time) {
  startTimedEvent(0, 0, time, EFFECT_STAGE);
}
