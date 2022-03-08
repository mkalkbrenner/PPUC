/*
  DistributionControllerTestButtons.h
  Created by Markus Kalkbrenner, 2022.

  Play more pinball!
*/

#ifndef EffectControllerTestButtons_h
#define EffectControllerTestButtons_h

#include <Arduino.h>
#include <Bounce2.h>

#include "../EventDispatcher/Event.h"
#include "../EventDispatcher/EventDispatcher.h"

class DistributionControllerTestButtons {
public:
    DistributionControllerTestButtons(EventDispatcher* eD);

    void update();

protected:
    EventDispatcher* eventDispatcher;
    Bounce2::Button* button[2];
};

#endif
