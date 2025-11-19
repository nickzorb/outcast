#include <Arduino.h>
#include "base.h"
#include "jumps.h"
#include "pins.h"
#include "timed.h"

byte stageJumpIndex[MAX_STAGES];

void jumpOfficePad(const unsigned long now) {
  return;
}

void jumpGasSliders(const unsigned long now) {
  stageJumpIndex[stage]++;
  setRelay(MAG_BARREL, ON);
  startTimedRelay(MAG_BARREL, OFF, now + 2000);
}
    
void jumpElevatorPad(const unsigned long now) {
}

void jumpBedUltrasound(const unsigned long now) {
}

void jumpSurgeryPanel(const unsigned long now) {
}

void jumpFridgeUrine(const unsigned long now) {
}

void jumpWcValves(const unsigned long now) {
}

void jumpWitnessStew(const unsigned long now) {
}

void jumpOvenKnobs(const unsigned long now) {
}

void jumpControlBarcode(const unsigned long now) {
}

void jumpBloodBars(const unsigned long now) {
}

void jumpIsoClock(const unsigned long now) {
}

void jumpPanelCellCables(const unsigned long now) {
}

void jumpPanelCafeFuses(const unsigned long now) {
}

void jumpPanelWcFuses(const unsigned long now) {
}

void jumpPanelBatteries(const unsigned long now) {
}

void jumpFinalUsb(const unsigned long now) {
}

void triggerJumpScareManual(const unsigned long now) {
  switch(stage) {
    case 0:
      break;
    case 1:
      jumpOfficePad(now);
      break;
    case 2:
      jumpGasSliders(now);
      break;
    case 3:
      jumpElevatorPad(now);
      break;
    case 4:
      jumpBedUltrasound(now);
      break;
    case 5:
      jumpSurgeryPanel(now);
      break;
    case 6:
      jumpFridgeUrine(now);
      break;
    case 7:
      jumpWcValves(now);
      break;
    case 8:
      jumpWitnessStew(now);
      break;
    case 9:
      jumpOvenKnobs(now);
      break;
    case 10:
      jumpControlBarcode(now);
      break;
    case 11:
      jumpBloodBars(now);
      break;
    case 12:
      jumpIsoClock(now);
      break;
    case 13:
      jumpPanelCellCables(now);
      break;
    case 14:
      jumpPanelCafeFuses(now);
      break;
    case 15:
      jumpPanelWcFuses(now);
      break;
    case 16:
      jumpPanelBatteries(now);
      break;
    case 17:
      jumpFinalUsb(now);
      break;
  }
}
