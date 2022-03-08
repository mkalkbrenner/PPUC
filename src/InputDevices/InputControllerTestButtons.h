/*
  InputControllerTestButtons.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef InputControllerTestButtons_h
#define InputControllerTestButtons_h

#include <Arduino.h>
#include <Bounce2.h>

#include "../EventDispatcher/Event.h"
#include "../EventDispatcher/EventDispatcher.h"

class InputControllerTestButtons {
public:
    InputControllerTestButtons(EventDispatcher* eD);

    void update();

protected:
    EventDispatcher* eventDispatcher;
    Bounce2::Button* button[2];
};

#endif
