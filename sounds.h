#pragma once
#include <Arduino.h>

//~~~~~~~SOUND IDS~~~~~~~~

#define CARPET          0
#define STORAGE         1
#define GAS_ROOM        2
#define CORRIDOR_START  3
#define ELEVATOR        4
#define BED_ABDUCTION   5
#define RUN_1           6
#define FRIDGE_SOUND    7
#define RUN_2           8
#define COFFEE_PLACE    9
#define PLEXIGLASS      10
#define CELL_SOUND      11
#define RUN_3           12
#define MURDER          13
#define END_MUSIC       14
#define SIREN           15
#define WOOD_CREAK      16
#define WHEELCHAIR      17
#define STINGER         18
#define ELECTRICITY     19

#define ALL_LOOPS       28
#define ALL_ONCE_OFFS   29
#define ALL_SOUNDS      30

//~~~~~~~OP CODES~~~~~~~~

#define LOOP_FADEIN     0
#define LOOP_NOW        1
#define STOP_LOOP_FADE  2
#define STOP_LOOP_NOW   3
#define ONCE_NOW        4
#define ONCE_FADE       5
#define STOP_FADE       6
#define STOP_NOW        7

#define KEEPALIVE       255
#define KEEPALIVE_MS    500


void playSound(byte opcode, byte id);
