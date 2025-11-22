#include <Arduino.h>
#include "flow.h"
#include "pins.h"
#include "base.h"
#include "lights.h"
#include "timed.h"
#include "sounds.h"

const byte PRINTER_CODE[] = { 0, 1, 2, 3 };

const StageFn stageHandlers[] = {
  updateNoop,
  updateStart,
  updateOfficeLaptop,
  updateOfficePad,
  updateGasSliders,
  updateNoop,
  updateNoop,
  updateElevatorPad,
  updateBedUltrasound,
  updateSurgeryPanel,
  updateFridgeUrine,
  updateWcValves,
  updateWitnessStew,
  updateOvenKnobs,
  updateControlBarcode,
  updateBloodBars,
  updateIsoClock,
  updatePC,
  updatePanelCellCables,
  updatePanelCafeFuses,
  updatePanelWcFuses,
  updatePanelBatteries,
  updateFinalUsb
};

const byte maxStage = sizeof(stageHandlers) / sizeof(stageHandlers[0]);

inline void printerBuzzClick() {
  tone(PRINTER_BUZZ, 3000, 40);
}

void updateNoop(unsigned long) {}

bool updatedStart = false;
void updateStart(const unsigned long now) {
  if (updatedStart) return;
  updatedStart = true;
  for (byte i = 0; i < LIGHT_COUNT; i++) {
    setLight(LIGHT_SOURCES[i], OFF);
  }
  setLight(LED_STORAGE, ON);
  setMagnet(POW_ULTRASOUND_A, ON);
  setRelay(POW_ULTRASOUND_B, ON);
  setRelay(POW_LAPTOP, ON);
  setRelay(POW_PC, ON);
  playSound(LOOP_FADEIN, STORAGE);
}

void solvedOfficeLaptop(const unsigned long now) {
  stage++;
  setLight(LED_MONEY_LAMP, ON);
  playSound(LOOP_FADEIN, STORAGE);
}

bool updatedOfficeLaptop = false;
void updateOfficeLaptop(const unsigned long now) {
  if (!updatedOfficeLaptop) {
    setLight(LED_STORAGE, OFF);
    playSound(STOP_FADE, STORAGE);
    digitalWrite(LAPTOP_NEXT, LOW);
    pinMode(LAPTOP_NEXT, OUTPUT);
    digitalWrite(LAPTOP_NEXT, LOW);
    delay(1000);
    pinMode(LAPTOP_NEXT, INPUT_PULLUP);
  }
  if (!saferDigitalRead(LAPTOP_IN) || bypassed) {
    solvedOfficeLaptop(now);
    bypassed = false;
  }
}

void solvedOfficePad(const unsigned long now) {
  stage++;
  pinMode(PRINTER_BUZZ, INPUT_PULLUP);
  setMagnet(MAG_STORAGE, OFF);
  setLight(LED_MONEY_LAMP, OFF);
  setLight(LED_GAS_ROOM, ON);
  playSound(STOP_LOOP_FADE, GAS_ROOM);
}

const byte PRINTER_BUTTONS[] = {
  PRINTER_A,
  PRINTER_B,
  PRINTER_C,
  PRINTER_D,
  PRINTER_OFF
};
byte printerProgress = 0;
bool printerLastPressed[] = {0, 0, 0, 0, 0};
void updateOfficePad(const unsigned long now) {
  if (bypassed) {
    solvedOfficePad(now);
    bypassed = false;
    return;
  }
  pinMode(PRINTER_BUZZ, OUTPUT);
  for (byte i = 0; i < 5; i++) {
    byte pin = PRINTER_BUTTONS[i];
    bool pressed = !saferDigitalRead(pin);
    if (pressed && !printerLastPressed[i]) {
      printerBuzzClick();
      if (i == PRINTER_CODE[printerProgress]) {
        printerProgress++;
        if (printerProgress >= sizeof(PRINTER_CODE)) {
          solvedOfficePad(now);
        }
      } else {
        if (i == PRINTER_CODE[0]) {
          printerProgress = 1;
        } else {
          printerProgress = 0;
        }
      }
    }
    printerLastPressed[i] = pressed;
  }
}

const int sliderCodeMin[] = {50, 250, 500, 70, 1000};
const int sliderCodeMax[] = {80, 255, 550, 90, 1023};
void solvedGasSliders(const unsigned long now) {
  stage++;
  setMagnet(MAG_GAS_ROOM, OFF);
  startTimedMagnet(MAG_GAS_ROOM, ON, now + 10000);
  setLight(LED_GAS_ROOM, OFF);
  setLight(LED_CORRIDOR_B, ON);
  playSound(STOP_LOOP_FADE, CORRIDOR_START);
}

void updateGasSliders(const unsigned long now) {
  if (bypassed) {
    solvedGasSliders(now);
    bypassed = false;
    return;
  }
  int sliderRead[5];
  sliderRead[0] = saferAnalogRead(SLIDER_A);
  sliderRead[1] = saferAnalogRead(SLIDER_B);
  sliderRead[2] = saferAnalogRead(SLIDER_C);
  sliderRead[3] = saferAnalogRead(SLIDER_D);
  sliderRead[4] = saferAnalogRead(SLIDER_E);
//  for (byte i = 0; i < 5; i++) {
//    Serial.print(sliderRead[i]);
//    Serial.print(" ");
//    delay(500);
//  }
//  Serial.println("");
  for (byte i = 0; i < 5; i++) {
    if (sliderRead[i] < sliderCodeMin[i] || sliderRead[i] > sliderCodeMax[i]) {
      return;
    }
  }
  solvedGasSliders(now);
}

const byte ultraLeds[] = {
  LED_ULTRA_LED_A,
  LED_ULTRA_LED_B,
  LED_ULTRA_LED_C,
  LED_ULTRA_LED_D,
  LED_ULTRA_LED_E,
  LED_ULTRA_LED_F
};
const byte ultraSpots[] = {
  LED_ULTRA_SPOT_A,
  LED_ULTRA_SPOT_B,
  LED_ULTRA_SPOT_C,
  LED_ULTRA_SPOT_D,
  LED_ULTRA_SPOT_E,
  LED_ULTRA_SPOT_F
};
const byte elevatorLeds[] = {
  LED_ELEVATOR_B,
  LED_ELEVATOR_A,
  LED_ELEVATOR_D,
  LED_ELEVATOR_F,
  LED_ELEVATOR_G,
  LED_ELEVATOR_C,
  LED_ELEVATOR_E
};
void solvedElevatorPad(const unsigned long now) {
  stage++;
  setMagnet(MAG_BED, OFF);
  setLight(LED_BED_MAIN, ON);
  for (byte i = 0; i < 6; i++) {
    setLight(ultraLeds[i], ON);
    setLight(elevatorLeds[i], OFF);
  }
  setLight(elevatorLeds[6], OFF);
  setLight(POW_ULTRASOUND_B, ON);
}

const byte elevatorCode[] = {2, 2, 3, 3, 0, 0, 1, 1, 4, 4};
const byte elevatorDigits[][7] = {
  {0, 1, 1, 0, 0, 0, 0},
  {1, 1, 0, 1, 1, 0, 1},
  {1, 1, 1, 1, 0, 0, 1},
  {1, 1, 1, 1, 1, 1, 0},
  {0, 0, 0, 0, 0, 0, 0}
};
byte curDigit = 10;
unsigned long elevatorPadLast = 0;
void updateElevatorPad(const unsigned long now) {
  if (bypassed) {
    solvedOfficePad(now);
    bypassed = false;
    return;
  }
  if (now - elevatorPadLast > 1 * 750) {
    curDigit = (curDigit + 1) % 10;
    for (byte i = 0; i < 7; i++) {
      setLight(elevatorLeds[i], elevatorDigits[elevatorCode[curDigit]][i]);
    }
    elevatorPadLast = now;
  }
  if (!saferDigitalRead(BED_PAD)) {
    solvedElevatorPad(now);
  }
}

void solvedBedUltrasound(const unsigned long now) {
  stage++;
}

void updateBedUltrasound(const unsigned long now) {
  if (bypassed) {
    solvedBedUltrasound(now);
    bypassed = false;
    return;
  }
}

void solvedSurgeryPanel(const unsigned long now) {
  stage++;

}

void updateSurgeryPanel(const unsigned long now) {
  if (bypassed) {
    solvedSurgeryPanel(now);
    bypassed = false;
    return;
  }
}

void solvedFridgeUrine(const unsigned long now) {
  stage++;

}

void updateFridgeUrine(const unsigned long now) {
  if (bypassed) {
    solvedFridgeUrine(now);
    bypassed = false;
    return;
  }
}

void solvedWcValves(const unsigned long now) {
  stage++;

}

void updateWcValves(const unsigned long now) {
  if (bypassed) {
    solvedWcValves(now);
    bypassed = false;
    return;
  }
}

void solvedWitnessStew(const unsigned long now) {
  stage++;

}

void updateWitnessStew(const unsigned long now) {
  if (bypassed) {
    solvedWitnessStew(now);
    bypassed = false;
    return;
  }
}

void solvedOvenKnobs(const unsigned long now) {
  stage++;

}

void updateOvenKnobs(const unsigned long now) {
  if (bypassed) {
    solvedOvenKnobs(now);
    bypassed = false;
    return;
  }

}

void solvedControlBarcode(const unsigned long now) {
  stage++;

}

void updateControlBarcode(const unsigned long now) {
  if (bypassed) {
    solvedControlBarcode(now);
    bypassed = false;
    return;
  }

}

void solvedBloodBars(const unsigned long now) {
  stage++;

}

void updateBloodBars(const unsigned long now) {
  if (bypassed) {
    solvedBloodBars(now);
    bypassed = false;
    return;
  }

}

void solvedIsoClock(const unsigned long now) {
  stage++;

}

void updateIsoClock(const unsigned long now) {
  if (bypassed) {
    solvedIsoClock(now);
    bypassed = false;
    return;
  }

}

void solvedPC(const unsigned long now) {
  stage++;

}

void updatePC(const unsigned long now) {
  if (bypassed) {
    solvedIsoClock(now);
    bypassed = false;
    return;
  }

}

void solvedPanelCellCables(const unsigned long now) {
  stage++;
  
}

void updatePanelCellCables(const unsigned long now) {
  if (bypassed) {
    solvedPanelCellCables(now);
    bypassed = false;
    return;
  }

}

void solvedPanelCafeFuses(const unsigned long now) {
  stage++;

}

void updatePanelCafeFuses(const unsigned long now) {
  if (bypassed) {
    solvedPanelCafeFuses(now);
    bypassed = false;
    return;
  }

}

void solvedPanelWcFuses(const unsigned long now) {
  stage++;

}

void updatePanelWcFuses(const unsigned long now) {
  if (bypassed) {
    solvedPanelWcFuses(now);
    bypassed = false;
    return;
  }

}

void solvedPanelBatteries(const unsigned long now) {
  stage++;

}

void updatePanelBatteries(const unsigned long now) {
  if (bypassed) {
    solvedPanelBatteries(now);
    bypassed = false;
    return;
  }

}

void solvedFinalUsb(const unsigned long now) {
  stage++;

}

void updateFinalUsb(const unsigned long now) {
  if (bypassed) {
    solvedFinalUsb(now);
    bypassed = false;
    return;
  }

}
