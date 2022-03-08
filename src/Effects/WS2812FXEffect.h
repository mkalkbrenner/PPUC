/*
  WS2812FXEffect.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef WS2812FXEffect_h
#define WS2812FXEffect_h

#include <Arduino.h>
#include <WS2812FX.h>

#include "Effect.h"
#include "../EffectDevices/EffectDevice.h"
#include "../EffectDevices/WS2812FXDevice.h"

class WS2812FXEffect : public Effect {
public:

    WS2812FXEffect(uint8_t mode, uint32_t color, uint16_t speed, uint8_t options, int duration = 0) {
        this->mode = mode;
        this->colors[0] = color;
        this->speed = speed;
        this->options = options;
        this->duration = duration;
    }

    WS2812FXEffect(uint8_t mode, const uint32_t colors[], uint16_t speed, uint8_t options, int duration = 0) {
        this->mode = mode;
        this->colors[0] = colors[0];
        this->colors[1] = colors[1];
        this->colors[2] = colors[2];
        this->speed = speed;
        this->options = options;
        this->duration = duration;
    }

    virtual void setDevice(EffectDevice* effectDevice);

    virtual void start(int repeat = 0);

    virtual void stop();

    virtual void update();

    int getFirstLED();
    int getlastLED();
    int getNumLEDs();

    int getFirstSegment();
    int getLastSegment();
    int getNumSegments();

protected:
    WS2812FX* ws2812FX;
    uint8_t mode;
    uint32_t colors[3] = {0, 0, 0};
    uint16_t speed;
    uint8_t options;
    int duration; // 0 means unlimited
};

#endif
