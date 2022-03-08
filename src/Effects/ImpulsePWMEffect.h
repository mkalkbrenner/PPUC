/*
  ImpulsePWMEffect.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef ImpulsePWMEffect_h
#define ImpulsePWMEffect_h

#include <Arduino.h>
#include <WavePWM.h>

#include "WavePWMEffect.h"
#include "../EffectDevices/EffectDevice.h"
#include "../EffectDevices/WavePWMDevice.h"

class ImpulsePWMEffect : public WavePWMEffect {
public:

    ImpulsePWMEffect(unsigned int frequency, uint8_t maxIntensity = 255) : WavePWMEffect(frequency, maxIntensity) {
        // nop
    }

    virtual void update();
};

#endif
