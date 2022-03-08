#include "DistributionController.h"

VPXComLink* DistributionController::vpxComLink() {
    return _vpxComLink;
}

DistributionControllerTestButtons* DistributionController::testButtons() {
    return _testButtons;
}

EventDispatcher* DistributionController::eventDispatcher() {
    return _eventDispatcher;
}
