/*
  PwmDevices.h
  Created by Markus Kalkbrenner, 2022.

  Play more pinball!
*/
#ifndef OUTPUT_PwmDevices_h
#define OUTPUT_PwmDevices_h

#define NUM_PINS 26

#include <Arduino.h>

#include "../EventDispatcher/Event.h"
#include "../EventDispatcher/EventDispatcher.h"

class PwmDevices {
public:
    //Constructor
    PwmDevices(byte bId, EventDispatcher* eD);

    void update();

private:
    EventDispatcher* eventDispatcher;
};


#endif
