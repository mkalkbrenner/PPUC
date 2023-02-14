/*
  IOBoardController.h
  Created by Markus Kalkbrenner, 20222.

  Play more pinball!

  GPIO0-7: Input (Switches) or low power output
  GPIO8-15: Input (Switches)
  GPIO16,17,18: UART TX, UART RX, RS485 Direction
  GPIO19-24, 26, 27: Power Out (PWM)
  GPIO25: Status-LED
  GPIO28: ADC für Adressierung
  GPIO29: Reserve (z.B. für einen LED-Strip oder zweite Status-LED)
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
    IOBoardController(int controllerType);

    PwmDevices* pwmDevices();

    Switches* switches();

    EventDispatcher* eventDispatcher();

    void handleEvent(Event* event) {}

    void handleEvent(ConfigEvent* event);

    void update();

private:
    PwmDevices* _pwmDevices;
    Switches* _switches;

    byte boardId;
    byte port = 0;
    byte number = 0;
    byte power = 0;
    byte minPulseTime = 0;
    byte maxPulseTime = 0;
    byte holdPower = 0;
    byte holdPowerActivationTime = 0;
    byte fastSwitch = 0;

    EventDispatcher* _eventDispatcher;
};

#endif
