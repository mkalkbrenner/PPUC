/*
  SwitchMatrix.h.
  Created by Markus Kalkbrenner, 2022.

  Play more pinball!
*/

#ifndef Switches_h
#define Switches_h

#include <Arduino.h>

#include "../EventDispatcher/Event.h"
#include "../EventDispatcher/EventDispatcher.h"

#ifndef MAX_SWITCHES
#define MAX_SWITCHES 16
#endif

#ifndef SWITCH_DEBOUNCE
#define SWITCH_DEBOUNCE 5
#endif

class Switches : public EventListener {
public:
    Switches(byte bId, EventDispatcher* eD) {
        boardId = bId;

        _eventDispatcher = eD;
        _eventDispatcher->addListener(this, EVENT_POLL_EVENTS);
        _eventDispatcher->addListener(this, EVENT_READ_SWITCHES);
    }

    void registerSwitch(byte p, byte n);

    void update();

    void handleEvent(Event* event);

    void handleEvent(ConfigEvent* event) {}

private:
    byte boardId;
    unsigned long _ms;

    byte port[MAX_SWITCHES] = {0};
    byte number[MAX_SWITCHES] = {0};
    bool state[MAX_SWITCHES] = {0};
    bool toggled[MAX_SWITCHES] = {0};
    byte last = 0;

    EventDispatcher* _eventDispatcher;
};

#endif
