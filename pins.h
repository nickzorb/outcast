#pragma once
#include <Arduino.h>
#include <Adafruit_MCP23X17.h>

//~~~~~~~RIDDLE PINS~~~~~~~~

#define LAPTOP_IN       2
#define LAPTOP_NEXT     3
#define LAPTOP_ALT      4
#define PRINTER_A       5
#define PRINTER_B       6
#define PRINTER_C       7
#define PRINTER_D       8
#define PRINTER_OFF     9
#define PRINTER_BUZZ    10
#define SLIDER_A        A0
#define SLIDER_B        A1
#define SLIDER_C        A2
#define SLIDER_D        A3
#define SLIDER_E        A4
#define BED_PAD         11
#define ULTRASOUND_A    12
#define ULTRASOUND_B    13
#define FRIDGE          14
#define VALVES          15
#define LETTERS_P       16
#define LETTERS_N       17
#define OVEN_A          18
#define OVEN_B          19
#define OVEN_C          22
#define OVEN_D          23
#define BARCODE_P       24
#define BARCODE_N       25
#define STEEL_BARS      26
#define CLOCK_P         27
#define CLOCK_R         28
#define CLOCK_B         29
#define BATTERIES       30
#define BATTERIES_BUZ   31
#define CABLES_AR       32
#define CABLES_BR       33
#define CABLES_CR       34
#define CABLES_DR       35
#define CABLES_ER       36
#define CABLES_FR       37
#define CABLES_AP       38
#define CABLES_BP       39
#define CABLES_CP       40
#define CABLES_DP       41
#define CABLES_EP       42
#define CABLES_FP       43
#define CABLES_BUZZ     44
#define SWITCHES_P      45
#define SWITCHES_N      46
#define SWITCHES_BUZZ   47
#define BREAKERS        48
#define BREAKERS_BUZZ   49
#define PC_A            50
#define PC_B            51
#define PC_C            52
#define CORRIDOR_PAD    53
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
#define LED_ELEVATOR_LED  6
#define LED_CORRIDOR_LED  7
#define LED_BED_MAIN      8
#define LED_ULTRA_SPOT_A  9
#define LED_ULTRA_SPOT_B  10
#define LED_ULTRA_SPOT_C  11
#define LED_ULTRA_SPOT_D  12
#define LED_ULTRA_SPOT_E  13
#define LED_ULTRA_SPOT_F  14
#define LED_ULTRA_LED_A   15
#define LED_ULTRA_LED_B   16
#define LED_ULTRA_LED_C   17
#define LED_ULTRA_LED_D   18
#define LED_ULTRA_LED_E   19
#define LED_ULTRA_LED_F   20
#define LED_FRIDGE        21
#define LED_WC            22
#define LED_OVEN          23
#define LED_OFFICE        24
#define LED_SECLUSION     25
#define LED_CELL_1        26
#define LED_CELL_2        27
#define LED_TUNNEL        28
#define LED_MONEY_LAMP    29
#define LED_CLOCK         30
#define LED_FINALE        31
#define LED_SIREN         32
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
#define MAG_PANS          71
#define MAG_BARREL        72
#define MAG_SAW           73

//~~~~~~~POWER PINS~~~~~~~~~

#define POW_LAPTOP        80
#define POW_ULTRASOUND_A  81
#define POW_ULTRASOUND_B  82
#define POW_BLOOD         83
#define POW_DRYER         84
#define POW_FANS          85
#define POW_PC            86
#define LED_FLY_CATCHER   87

//~~~~~~AUXILARY~~~~~~~~~~~

#define OFF               false
#define ON                true

#define RELAY_ADDRESS       32
#define RELAY_CONTROLS      6
#define RELAYS_PER_CONTROL  16

extern Adafruit_MCP23X17 relayControls[RELAY_CONTROLS];

void setupControls();
void setupInputs();
void setRelay(byte logicalPin, bool on);
