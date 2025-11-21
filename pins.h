#pragma once
#include <Arduino.h>
#include <Adafruit_MCP23X17.h>

//~~~~~~~RIDDLE PINS~~~~~~~~

#define LAPTOP_IN       2
#define LAPTOP_NEXT     3
#define PRINTER_A       7
#define PRINTER_B       5
#define PRINTER_C       6
#define PRINTER_D       4
#define PRINTER_OFF     8
#define PRINTER_BUZZ    9
#define SLIDER_A        A0
#define SLIDER_B        A1
#define SLIDER_C        A2
#define SLIDER_D        A3
#define SLIDER_E        A4
#define BED_PAD         10
#define ULTRASOUND_A    11
#define ULTRASOUND_B    12
#define FRIDGE          13
#define VALVES          14
#define LETTERS_P       15
#define LETTERS_N       16
#define OVEN_A          17
#define OVEN_B          18
#define OVEN_C          19
#define OVEN_D          22
#define BARCODE_P       23
#define BARCODE_N       24
#define STEEL_BARS      25
#define CLOCK_P         26
#define CLOCK_R         27
#define CLOCK_B         28
#define BATTERIES       29
#define BATTERIES_BUZ   30
#define CABLES_AR       31
#define CABLES_BR       32
#define CABLES_CR       33
#define CABLES_DR       34
#define CABLES_ER       35
#define CABLES_FR       36
#define CABLES_AP       37
#define CABLES_BP       38
#define CABLES_CP       39
#define CABLES_DP       40
#define CABLES_EP       41
#define CABLES_FP       42
#define CABLES_BUZZ     43
#define SWITCHES_P      44
#define SWITCHES_N      45
#define SWITCHES_BUZZ   46
#define BREAKERS        47
#define BREAKERS_BUZZ   48
#define PC_A            49
#define PC_B            50
#define PC_C            51
#define CORRIDOR_PAD    52
#define CONTROLLER_A    A6
#define CONTROLLER_B    A7
#define CONTROLLER_C    A8
#define CONTROLLER_D    A9
#define CONTROLLER_E    A10
#define CONTROLLER_F    A11
#define CONTROLLER_G    A12
#define CONTROLLER_H    A13
#define CONTROLLER_BYP  A14
#define LANGUAGE        A15

//~~~~~~~LIGHT PINS~~~~~~~~~

#define LED_STORAGE       0
#define LED_GAS_ROOM      1
#define LED_CORRIDOR_A    2
#define LED_CORRIDOR_B    3
#define LED_CORRIDOR_C    4
#define LED_ELEVATOR_SPOT 5
#define LED_ELEVATOR_LED  37
#define LED_CORRIDOR_RED  7
#define LED_CORRIDOR_WH   8
#define LED_BED_MAIN      9
#define LED_ULTRA_SPOT_A  10
#define LED_ULTRA_SPOT_B  11
#define LED_ULTRA_SPOT_C  12
#define LED_ULTRA_SPOT_D  13
#define LED_ULTRA_SPOT_E  14
#define LED_ULTRA_SPOT_F  15
#define LED_ULTRA_LED_A   16
#define LED_ULTRA_LED_B   17
#define LED_ULTRA_LED_C   18
#define LED_ULTRA_LED_D   19
#define LED_ULTRA_LED_E   20
#define LED_ULTRA_LED_F   21
#define LED_FRIDGE        22
#define LED_WC            23
#define LED_OFFICE        24
#define LED_FANS          36
#define LED_CELL_1        26
#define LED_CELL_2        27
#define LED_TUNNEL        28
#define LED_MONEY_LAMP    29
#define LED_FINALE        30
#define LED_SIREN         31
#define LED_PAD_CORRIDOR  32
#define LED_PAD_BED       33
#define LED_CLOCK         34
#define LED_OVEN          35
#define LED_ELEVATOR_A    41
#define LED_ELEVATOR_B    42
#define LED_ELEVATOR_C    43
#define LED_ELEVATOR_D    44
#define LED_ELEVATOR_E    45
#define LED_ELEVATOR_F    46
#define LED_ELEVATOR_G    47

//~~~~~~~MAGNET PINS~~~~~~~~~

#define MAG_ENTER         48
#define MAG_STORAGE       49
#define MAG_GAS_ROOM      50
#define MAG_ELEVATOR      51
#define MAG_BED           52
#define MAG_FRIDGE_ABD    53
#define MAG_FRIDGE_RIDD   54
#define MAG_WC            55
#define MAG_GAS_WC        56
#define MAG_TOILET        57
#define MAG_COFFEE        58
#define MAG_VENTILATION   59
#define MAG_ISOLATION     60
#define MAG_OFFICE        61
#define MAG_CELLS         62
#define MAG_TUNNEL        63
#define MAG_STEEL_BARS    64
#define MAG_PLEXI         65
#define MAG_GM            66
#define MAG_BATTERIES     67
#define MAG_CABLES        68
#define MAG_SWITCHES      69
#define MAG_BREAKERS      70
#define MAG_PANS          72
#define MAG_SAW           73
#define MAG_BARREL        74

//~~~~~~~POWER PINS~~~~~~~~~

#define POW_LAPTOP        80
#define POW_ULTRASOUND_A  81
#define POW_ULTRASOUND_B  82
#define POW_BLOOD         83
#define POW_DRYER         84
#define POW_FANS          85
#define POW_PC            86
#define LED_FLY_CATCHER   94

//~~~~~~AUXILARY~~~~~~~~~~~

#define OFF               false
#define ON                true

#define RELAY_ADDRESS       32
#define RELAY_CONTROLS      6
#define RELAYS_PER_CONTROL  16

extern Adafruit_MCP23X17 relayControls[RELAY_CONTROLS];

void setupControls();
void setupInputs();
void setRelay(byte id, bool on);
void setMagnet(byte id, bool on);
