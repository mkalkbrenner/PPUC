/*
  WavePWMEffect.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef WavePWMEffect_h
#define WavePWMEffect_h

#include <Arduino.h>
#include <WavePWM.h>

#include "Effect.h"
#include "../EffectDevices/EffectDevice.h"
#include "../EffectDevices/WavePWMDevice.h"

class WavePWMEffect : public Effect {
public:

    WavePWMEffect(unsigned int frequency, uint8_t maxIntensity = 255, uint8_t minIntensity = 0) {
        this->waveDuration = 1000 / frequency;
        this->maxIntensity = maxIntensity;
        this->minIntensity = minIntensity;
        this->compression = 255 / (maxIntensity - minIntensity);
    }

    virtual void setDevice(EffectDevice* effectDevice);

    virtual void start(int repeat = 0);

    virtual void stop();

    virtual void update() = 0;

protected:
    WavePWM* wavePWM;
    unsigned int waveDuration;
    uint8_t maxIntensity;
    uint8_t minIntensity;
    uint8_t compression;
};

#endif
