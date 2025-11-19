#include <Arduino.h>
#include "flow.h"
#include "pins.h"
#include "base.h"
#include "timed.h"

const byte PRINTER_BUTTONS[] = {
  PRINTER_A,
  PRINTER_B,
  PRINTER_C,
  PRINTER_D,
  PRINTER_OFF
};

const byte PRINTER_CODE[] = { 0, 1, 2, 3 };

static byte printerProgress = 0;
static bool printerLastPressed[] = {0, 0, 0, 0, 0};

inline void printerBuzzClick() {
  tone(PRINTER_BUZZ, 3000, 40);
}

void solvedOfficePad(const unsigned long now) {
  stage++;
  setRelay(MAG_STORAGE, OFF);
  startTimedRelay(MAG_STORAGE, ON, now + 15000);
  pinMode(PRINTER_BUZZ, INPUT_PULLUP);
  printerProgress = 0;
  for (byte i = 0; i < 5; i++) printerLastPressed[i] = 0;
}

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
  setRelay(MAG_GAS_ROOM, OFF);
  startTimedRelay(MAG_GAS_ROOM, ON, now + 15000);
}

void updateGasSliders(const unsigned long now) {
  if (bypassed) {
    solvedOfficePad(now);
    bypassed = false;
    return;
  }
  const int sliderRead[] = {
    saferAnalogRead(SLIDER_A),
    saferAnalogRead(SLIDER_B),
    saferAnalogRead(SLIDER_C),
    saferAnalogRead(SLIDER_D),
    saferAnalogRead(SLIDER_E)
  };
  for (byte i = 0; i < 5; i++) {
    if (sliderRead[i] < sliderCodeMin[i] || sliderRead[i] > sliderCodeMax[i]) {
      return;
    }
  }
  solvedGasSliders(now);
}

void solvedElevatorPad(const unsigned long now) {
  stage++;
  setRelay(MAG_BED, OFF);
}

void updateElevatorPad(const unsigned long now) {
  if (bypassed) {
    solvedOfficePad(now);
    bypassed = false;
    return;
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
