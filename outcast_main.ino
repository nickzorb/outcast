#include "pins.h"
#include "sounds.h"
#include "lights.h"
#include "flow.h"
#include "jumps.h"
#include "timed.h"

unsigned long lastKeepAliveMs = 0;

void sendKeepAliveIfDue(unsigned long nowMs) {
  if (nowMs - lastKeepAliveMs >= KEEPALIVE_MS) {
    Serial.write(KEEPALIVE);
    Serial.flush();
    lastKeepAliveMs = nowMs;
  }
}

void setup() {
  Serial.begin(115200);
  setupControls();
  setupInputs();
  setupLights();
}

void loop() {
  const unsigned long now = millis();
  sendKeepAliveIfDue(now);
  handleRemote(now);
  performStageStep(now);
  performJumpScare(now);
  updateTimedEffects(now);
}

bool lastState[9] = {false};

void handleRemote(const unsigned long now) {
  bool state[9];
  state[0] = !saferDigitalRead(CONTROLLER_A);
  state[1] = !saferDigitalRead(CONTROLLER_B);
  state[2] = !saferDigitalRead(CONTROLLER_C);
  state[3] = !saferDigitalRead(CONTROLLER_D);
  state[4] = !saferDigitalRead(CONTROLLER_E);
  state[5] = !saferDigitalRead(CONTROLLER_F);
  state[6] = !saferDigitalRead(CONTROLLER_G);
  state[7] = !saferDigitalRead(CONTROLLER_H);
  state[8] = (saferAnalogRead(CONTROLLER_BYP) < 900);

  for (byte i = 0; i < 9; i++) {
    if (state[i] && !lastState[i]) {
      onRemoteChange(i, true, now);
    } else if (lastState[i] && !state[i]) {
      onRemoteChange(i, false, now);
    }
    lastState[i] = state[i];
  }
}

void onRemoteChange(const byte button, const bool pressed, const unsigned long now) {
  switch (button) {
    case 0:
      if (pressed && (stage == 0 || stage == 1 || stage == 15)) stage++;
      break;
    case 1: if (pressed) doBlackout(); break;
    case 2: setRelay(MAG_GM, pressed); break;
    case 3: if (pressed) stageJumpIndex[stage]++; break;
    case 4: setRelay(MAG_GAS_ROOM, pressed); setRelay(MAG_GAS_WC, pressed); break;
    case 5: setRelay(MAG_ISOLATION, pressed); break;
    case 6: setRelay(MAG_CELLS, pressed); break;
    case 7: setRelay(MAG_OFFICE, pressed); break;
    case 8: if (pressed) bypassed = true; break;
  }
}

void performStageStep(const unsigned long now) {
  if (stage >= maxStage) return;
  stageHandlers[stage](now);
}
