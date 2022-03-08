/*
  CrossLinkDebugger.h
  Created by Markus Kalkbrenner, 2020-2021.

  Play more pinball!
*/

#ifndef CROSSLINKDEBUGGER_h
#define CROSSLINKDEBUGGER_h

#include <Arduino.h>

#include "Event.h"
#include "EventListener.h"

class CrossLinkDebugger : public EventListener {
public:
    CrossLinkDebugger() {}

    void handleEvent(Event* event);
};

#endif
