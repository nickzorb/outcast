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
  state[8] = !saferDigitalRead(CONTROLLER_BYP);

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
      if(pressed && stage == 0) {
        stage = 1;
        setRelay(MAG_ENTER, OFF);
        startTimedRelay(MAG_ENTER, ON, now + 5000);
      }
      break;
    case 1: if (pressed) doBlackout(); break;
    case 2: setRelay(MAG_GM, !pressed); break;
    case 3: if (pressed) triggerJumpScareManual(now); break;
    case 4: setRelay(MAG_GAS_ROOM, !pressed); setRelay(MAG_GAS_WC, !pressed); break;
    case 5: setRelay(MAG_ISOLATION, !pressed); break;
    case 6: setRelay(MAG_CELLS, !pressed); break;
    case 7: setRelay(MAG_OFFICE, !pressed); break;
    case 8: bypassed = true;
  }
}

void performStageStep(const unsigned long now) {
  switch(stage) {
    case 0:
      break;
    case 1:
      updateOfficePad(now);
      break;
    case 2:
      updateGasSliders(now);
      break;
    case 3:
      updateElevatorPad(now);
      break;
    case 4:
      updateBedUltrasound(now);
      break;
    case 5:
      updateSurgeryPanel(now);
      break;
    case 6:
      updateFridgeUrine(now);
      break;
    case 7:
      updateWcValves(now);
      break;
    case 8:
      updateWitnessStew(now);
      break;
    case 9:
      updateOvenKnobs(now);
      break;
    case 10:
      updateControlBarcode(now);
      break;
    case 11:
      updateBloodBars(now);
      break;
    case 12:
      updateIsoClock(now);
      break;
    case 13:
      updatePanelCellCables(now);
      break;
    case 14:
      updatePanelCafeFuses(now);
      break;
    case 15:
      updatePanelWcFuses(now);
      break;
    case 16:
      updatePanelBatteries(now);
      break;
    case 17:
      updateFinalUsb(now);
      break;
  }
}