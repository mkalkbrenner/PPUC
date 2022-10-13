/*
  DistributionController.h
  Created by Markus Kalkbrenner, 2020-2021.

  Play more pinball!
*/

#ifndef DISTRIBUTIONCONTROLLER_h
#define DISTRIBUTIONCONTROLLER_h

#include <Arduino.h>

#include "EventDispatcher/EventDispatcher.h"
#include "EventDispatcher/EventListener.h"
#include "InputDevices/DistributionControllerTestButtons.h"
#include "VisualPinball/VPXComLink.h"

class DistributionController {
public:
    DistributionController(String controllerType, byte pf) {
        platform = pf;
        _eventDispatcher = new EventDispatcher();

        if (controllerType == "0.1.0") {
            _vpxComLink = new VPXComLink(_eventDispatcher, platform);
            _testButtons = new DistributionControllerTestButtons(_eventDispatcher);

            _eventDispatcher->addListener(_vpxComLink, EVENT_SOURCE_SWITCH);
        } else {
            Serial.print("Unsupported Distribution Controller: ");
            Serial.println(controllerType);
        }
    }

    VPXComLink* vpxComLink();

    DistributionControllerTestButtons* testButtons();

    EventDispatcher* eventDispatcher();

    byte platform;

private:
    VPXComLink* _vpxComLink;
    DistributionControllerTestButtons* _testButtons;
    EventDispatcher* _eventDispatcher;
};

#endif
