/*
  PIN2DMD.h
  Created by Markus Kalkbrenner, 2020-2021.

  Play more pinball!
*/

#ifndef PIN2DMD_h
#define PIN2DMD_h

#include <Arduino.h>

#include "../EventDispatcher/Event.h"
#include "../EventDispatcher/EventDispatcher.h"

class PIN2DMD {
public:
    PIN2DMD(EventDispatcher* eD) {
        eventDispatcher = eD;
    }

    void setSerial(HardwareSerial &reference);

    void update();

    void setDebug(bool value);

private:
    EventDispatcher* eventDispatcher;

    HardwareSerial* hwSerial;

    bool debug = false;

};

#endif
