/*
  EventListener.h
  Created by Markus Kalkbrenner, 2020-2021.

  Play more pinball!
*/

#ifndef EVENTLISTENER_h
#define EVENTLISTENER_h

#include "Event.h"

class EventListener {
public:
    virtual void handleEvent(Event* event) = 0;
};

#endif
