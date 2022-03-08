/*
  SinePWMEffect.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef SinePWMEffect_h
#define SinePWMEffect_h

#include <Arduino.h>
#include <WavePWM.h>

#include "WavePWMEffect.h"
#include "../EffectDevices/EffectDevice.h"
#include "../EffectDevices/WavePWMDevice.h"

class SinePWMEffect : public WavePWMEffect {
public:

    SinePWMEffect(unsigned int frequency, unsigned int duration, uint8_t maxIntensity = 255, uint8_t minIntensity = 0) : WavePWMEffect(frequency, maxIntensity, minIntensity) {
        this->duration = duration;
        this->rampCompression = 255 / maxIntensity;
    }

    virtual void update();

protected:
    unsigned int duration;
    uint8_t rampCompression;
};

#endif
