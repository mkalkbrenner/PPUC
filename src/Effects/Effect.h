/*
  Effect.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef EFFECT_h
#define EFFECT_h

#include <Arduino.h>

#include "../EffectDevices/EffectDevice.h"
#include "../EventDispatcher/EventDispatcher.h"
#include "../EventDispatcher/Event.h"

class Effect {
public:
    Effect();

    bool isRunning();

    virtual void start(int repeat = 0);

    virtual void stop();

    virtual void terminate();

    virtual void update() = 0;

    virtual void updateMillis();

    virtual void resetMillis();

    void setEventDispatcher(EventDispatcher* eD);

    virtual void setDevice(EffectDevice* effectDevice);

protected:
    void dispatch(Event* event);

    EventDispatcher* eventDispatcher;
    EffectDevice* device;

    bool running = false;
    int repeat = 0; // -1 is endless, 0 means play once, 3 means repeat three times, ...
    unsigned int ms;
    unsigned long _ms;
    int stage = 0;
};

#endif
