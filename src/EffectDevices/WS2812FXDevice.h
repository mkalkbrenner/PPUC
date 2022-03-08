/*
  WS2812FXDevice.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef WS2812FXDevice_h
#define WS2812FXDevice_h

#include <Arduino.h>
#include <WS2812FX.h>

#include "EffectDevice.h"

#define RGBW_BLACK      (uint32_t)0x00000000
#define RGBW_PUREWHITE  (uint32_t)0xFF000000
#define RGBW_ULTRAWHITE (uint32_t)0xFFFFFFFF

class WS2812FXDevice : public EffectDevice {
public:
    WS2812FXDevice(WS2812FX* ws2812FX, int firstLED, int lastLED, int firstSegment, int lastSegment) {
        this->ws2812FX = ws2812FX;
        this->firstLED = firstLED;
        this->lastLED = lastLED;
        this->firstSegment = firstSegment;
        this->lastSegment = lastSegment;
    }

    virtual void on();

    virtual void off();

    void reset();

    WS2812FX* getWS2812FX();

    int getFirstLED();
    int getlastLED();
    int getNumLEDs();

    int getFirstSegment();
    int getLastSegment();
    int getNumSegments();

    bool isStopped();

    void setBrightness(byte b);
    byte getBrightness();

    void _reduceLEDs(int lastLED, int lastSegment) {
        this->lastLED = lastLED;
        this->lastSegment = lastSegment;
    }

    bool hasAfterGlowSupport() {
        return afterGlowSupport;
    };

protected:
    WS2812FX* ws2812FX;

    int firstLED;
    int lastLED;
    int firstSegment;
    int lastSegment;

    byte brightness = 64;

    bool stopped = true;
    bool afterGlowSupport = false;
};

#endif
