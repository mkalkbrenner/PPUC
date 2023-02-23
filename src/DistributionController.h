/*
  DistributionController.h
  Created by Markus Kalkbrenner.
*/

#ifndef DISTRIBUTIONCONTROLLER_h
#define DISTRIBUTIONCONTROLLER_h

#include "PPUC.h"

#include "EventDispatcher/EventDispatcher.h"
#include "EventDispatcher/EventListener.h"
#include "InputDevices/DistributionControllerTestButtons.h"
#include "VisualPinball/VPXComLink.h"

class DistributionController {
public:
    DistributionController(int controllerType, byte pf) {
        platform = pf;
        _eventDispatcher = new EventDispatcher();

        if (controllerType == CONTROLLER_MEGA_ALL_INPUT) {
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
