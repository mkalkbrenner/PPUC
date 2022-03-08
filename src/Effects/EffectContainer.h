/*
  EffectContainer.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef EFFECTCONTAINER_h
#define EFFECTCONTAINER_h

#include "Effect.h"
#include "../EffectDevices/EffectDevice.h"
#include "../EventDispatcher/Event.h"

struct EffectContainer {

    Effect* effect;
    EffectDevice* device;
    Event* event;
    int priority; // 0 = default, higher value means higher priority
    int repeat; // 0 = no repeat, >=1 times repeat
    int mode; // -1 = always, 0 = normal play, >=1 multiball, mode, scene, ball save ...

    EffectContainer(Effect* ef, EffectDevice* d, Event* ev, int p) {
        effect = ef;
        device = d;
        event = ev;
        priority = p;
        repeat = 1;
        mode = 0;
    }

    EffectContainer(Effect* ef, EffectDevice* d, Event* ev, int p, int r) {
        effect = ef;
        device = d;
        event = ev;
        priority = p;
        repeat = r;
        mode = 0;
    }

    EffectContainer(Effect* ef, EffectDevice* d, Event* ev, int p, int r, int m) {
        effect = ef;
        device = d;
        event = ev;
        priority = p;
        repeat = r;
        mode = m;
    }
};

#endif
