/*
  VPXComLink.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef VPXCOMLINK_h
#define VPXCOMLINK_h

#include <Arduino.h>

#include "../EventDispatcher/Event.h"
#include "../EventDispatcher/EventDispatcher.h"
#include "../EventDispatcher/EventListener.h"

class VPXComLink : public EventListener {
public:
    VPXComLink(EventDispatcher* eD, byte pf) {
        eventDispatcher = eD;
        platform = pf;
    }

    void update();

    void handleEvent(Event* event);

    void handleEvent(ConfigEvent* event) {}

private:
    EventDispatcher* eventDispatcher;

    byte platform;

};

#endif
