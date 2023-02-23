/*
  PPUC.h
  Created by Markus Kalkbrenner.
*/

#ifndef PPUC_h
#define PPUC_h

#include <Arduino.h>

#define CONTROLLER_MEGA_ALL_INPUT   1
#define CONTROLLER_TEENSY_OUTPUT    10
#define CONTROLLER_TEENSY_OUTPUT_2  11
#define CONTROLLER_NANO_PIN2DMD_GI  20
#define CONTROLLER_16_8_1           30

#define PLATFORM_WPC        1
#define PLATFORM_DATA_EAST  2
#define PLATFORM_SYS11      3
#define PLATFORM_LIBPINMAME 100

typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT32;

#include <EffectDevices/Definitions.h>

#endif
