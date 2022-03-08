/*
  RGBColorCycleEffect.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef RGBColorCycleEffect_h
#define RGBColorCycleEffect_h

#include <Arduino.h>

#include "Effect.h"
#include "../EffectDevices/WS2812FXDevice.h"

class RGBColorCycleEffect : public Effect {
public:
    RGBColorCycleEffect(unsigned int delayMs) {
        delay = delayMs;
    }

    void update();

protected:
    unsigned int delay;
    uint32_t color;
};

#endif
