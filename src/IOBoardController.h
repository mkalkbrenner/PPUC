/*
  IOBoardController.h
  Created by Markus Kalkbrenner, 20222.

  Play more pinball!
*/

#ifndef IOBOARDCONTROLLER_h
#define IOBOARDCONTROLLER_h

#include <Arduino.h>

#include "EventDispatcher/Event.h"
#include "EventDispatcher/EventDispatcher.h"
#include "IODevices/PwmDevices.h"
#include "IODevices/Switches.h"

class IOBoardController : public EventListener {
public:
    IOBoardController(String controllerType);

    PwmDevices* pwmDevices();

    Switches* switches();

    EventDispatcher* eventDispatcher();

    void handleEvent(Event* event) {}

    void handleEvent(ConfigEvent* event);

private:
    PwmDevices* _pwmDevices;
    Switches* _switches;

    byte boardId;
    byte port = 0;
    byte number = 0;

    EventDispatcher* _eventDispatcher;
};

#endif
