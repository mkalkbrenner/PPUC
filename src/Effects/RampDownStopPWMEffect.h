/*
  RampDownStopPWMEffect.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef RampDownStopPWMEffect_h
#define RampDownStopPWMEffect_h

#include <Arduino.h>
#include <WavePWM.h>

#include "WavePWMEffect.h"
#include "../EffectDevices/EffectDevice.h"
#include "../EffectDevices/WavePWMDevice.h"

class RampDownStopPWMEffect : public WavePWMEffect {
public:

    RampDownStopPWMEffect(unsigned int frequency) : WavePWMEffect(frequency) {
        // nop
    }

    virtual void updateMillis();

    virtual void update();
};

#endif
