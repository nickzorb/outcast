#include <Arduino.h>
#include "base.h"
#include "jumps.h"
#include "pins.h"
#include "timed.h"
#include "lights.h"
#include "sounds.h"

byte stageJumpIndex[MAX_STAGES];

void jumpNoop(const unsigned long now) {}

void jumpStart(const unsigned long now) {}

void jumpOfficeLaptop(const unsigned long now) {}

byte jumpOfficePadPrevStage = 0;
void jumpOfficePad(const unsigned long now) {
  if (stageJumpIndex[stage] == jumpOfficePadPrevStage) return;
  setLight(LED_MONEY_LAMP, OFF);
  startTimedLight(LED_MONEY_LAMP, ON, now + 500);
  startTimedLight(LED_MONEY_LAMP, OFF, now + 1500);
  startTimedLight(LED_MONEY_LAMP, ON, now + 2000);
  jumpOfficePadPrevStage = stageJumpIndex[stage];
}

byte jumpGasSlidersPrevStage = 0;
void jumpGasSliders(const unsigned long now) {
  if (stageJumpIndex[stage] == jumpGasSlidersPrevStage) return;
  setRelay(MAG_BARREL, ON);
  startTimedRelay(MAG_BARREL, OFF, now + 2000);
  jumpGasSlidersPrevStage = stageJumpIndex[stage];
}

void jumpElevatorDown(const unsigned long now) {
  if (stageJumpIndex[stage] != 1) return;
  stageJumpIndex[stage]++;
  setLight(LED_CORRIDOR_B, OFF);
  playSound(ALL_SOUNDS, STOP_FADE);
  playSound(ONCE_NOW, ELEVATOR);
  setLight(LED_ELEVATOR_LED, ON);
  startTimedMagnet(MAG_ELEVATOR, OFF, now + 18 * 1000);
  startTimedMagnet(MAG_ELEVATOR, ON, now + 19 * 1000);
  startTimedMagnet(MAG_BED, OFF, now + 18 * 1000);
  startTimedMagnet(MAG_BED, ON, now + 19 * 1000);
  startTimedLight(LED_ELEVATOR_LED, OFF, now + 19 * 1000);
  startTimedLight(LED_ELEVATOR_SPOT, ON, now + 19 * 1000);
  startTimedLight(LED_ELEVATOR_SPOT, OFF, now + 22 * 1000);
  startTimedSound(CARPET, LOOP_FADEIN, now + 26 * 1000);
  startTimedStage(now + 26 * 1000);
}

unsigned long jumpAbductionLastTime = 0;
bool jumpAbductionState = ON;
void jumpAbduction(const unsigned long now) {
  if (stageJumpIndex[stage] == 1) {
    stageJumpIndex[stage]++;
    jumpAbductionLastTime = now;
    playSound(STOP_LOOP_NOW, BED_ABDUCTION);
    setLight(LED_BED_MAIN, jumpAbductionState);
  } else if (stageJumpIndex[stage] == 2) {
    if (jumpAbductionState && now - jumpAbductionLastTime > 200) {
      jumpAbductionState != jumpAbductionState;
      setLight(LED_BED_MAIN, jumpAbductionState);
    } else if (!jumpAbductionState && now - jumpAbductionLastTime > 1000) {
      jumpAbductionState != jumpAbductionState;
      setLight(LED_BED_MAIN, jumpAbductionState);
    }
  } else if (stageJumpIndex[stage] == 3) {
    stageJumpIndex[stage]++;
    setLight(LED_BED_MAIN, OFF);
    setLight(LED_CORRIDOR_C, ON);
    startTimedLight(LED_CORRIDOR_C, OFF, now + 1 * 1000);
    startTimedLight(LED_CORRIDOR_B, ON, now + 3 * 1000);
    startTimedLight(LED_CORRIDOR_B, OFF, now + 4 * 1000);
    startTimedMagnet(MAG_GM, OFF, now + 5 * 1000);
    startTimedMagnet(MAG_FRIDGE_ABD, OFF, now + 5 * 1000);
    startTimedMagnet(MAG_GM, ON, now + 6 * 1000);
    startTimedMagnet(MAG_FRIDGE_ABD, ON, now + 6 * 1000);
    startTimedSound(CARPET, STOP_LOOP_FADE, now + 9 * 1000);
    startTimedLight(LED_BED_MAIN, ON, now + 10 * 1000);
    startTimedLight(LED_PAD_BED, ON, now + 10 * 1000);
    startTimedStage(now + 11 * 1000);
  }
}

void jumpElevatorPad(const unsigned long now) {}

const byte ultraJumpLights[] = {
  LED_ULTRA_LED_A,
  LED_ULTRA_LED_B,
  LED_ULTRA_LED_C,
  LED_ULTRA_LED_D,
  LED_ULTRA_LED_E,
  LED_ULTRA_LED_F,
  LED_CORRIDOR_A,
  LED_CORRIDOR_B,
  LED_CORRIDOR_C
};
const byte ultraJumpLightStatus[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned long jumpBedUltraLast = 0;
void jumpBedUltrasound(const unsigned long now) {
  if (stageJumpIndex[stage] == 1) {
    stageJumpIndex[stage]++;
    playSound(STOP_LOOP_NOW, RUN_1);
    setLight(POW_ULTRASOUND_B, OFF);
    setMagnet(MAG_FRIDGE_ABD, OFF);
    setLight(LED_BED_MAIN, OFF);
    for (byte i = 0; i < 9; i++) {
      setLight(ultraJumpLights[i], ultraJumpLightStatus[i]);
    }
  }
  if (stageJumpIndex[stage] == 2) {
    if (now - jumpBedUltraLast < 300) return;
    jumpBedUltraLast = now;
    for (byte i = 0; i < 9; i++) {
      setLight(ultraJumpLights[i], random(5) >= 4);
    }
  }
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

void jumpPC(const unsigned long now) {

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

const StageFn jumpHandlers[] = {
  jumpNoop,
  jumpStart,
  jumpOfficeLaptop,
  jumpOfficePad,
  jumpGasSliders,
  jumpElevatorDown,
  jumpAbduction,
  jumpElevatorPad,
  jumpBedUltrasound,
  jumpSurgeryPanel,
  jumpFridgeUrine,
  jumpWcValves,
  jumpWitnessStew,
  jumpOvenKnobs,
  jumpControlBarcode,
  jumpBloodBars,
  jumpIsoClock,
  jumpPC,
  jumpPanelCellCables,
  jumpPanelCafeFuses,
  jumpPanelWcFuses,
  jumpPanelBatteries,
  jumpFinalUsb
};

const byte maxJump = sizeof(jumpHandlers) / sizeof(jumpHandlers[0]);

void performJumpScare(const unsigned long now) {
  if (stage >= maxJump) return;
  jumpHandlers[stage](now);
}
