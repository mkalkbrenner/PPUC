/*
  LedBuiltInDevice.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef LedBuiltInDevice_h
#define LedBuiltInDevice_h

#include <Arduino.h>

#include "EffectDevice.h"

class LedBuiltInDevice : public EffectDevice {
public:
    LedBuiltInDevice() {
        pinMode(LED_BUILTIN, OUTPUT);
    }

    void on();

    void reset();

};

#endif
