#include "InputController.h"

InputController::InputController(int controllerType, byte pf) {
    _eventDispatcher = new EventDispatcher();
    InputController(controllerType, pf, _eventDispatcher);
}

InputController::InputController(int controllerType, byte pf, EventDispatcher* eventDispatcher) {
    pinMode(LED_BUILTIN, OUTPUT);

    platform = pf;
    _eventDispatcher = eventDispatcher;

    if (controllerType == CONTROLLER_MEGA_ALL_INPUT) {
        _solenoids = new Solenoids(controllerType, _eventDispatcher);
        _switchMatrix = new SwitchMatrix(_eventDispatcher, platform);
        _lightMatrix = new LightMatrix(_eventDispatcher, platform);
        _pin2Dmd = new PIN2DMD(_eventDispatcher);
        _pupComLink = new PUPComLink();
        _testButtons = new InputControllerTestButtons(_eventDispatcher);
    }
    else if (controllerType == CONTROLLER_NANO_PIN2DMD_OUTPUT) {
        _pin2Dmd = new PIN2DMD(_eventDispatcher);
    } else {
        Serial.print("Unsupported Input Controller: ");
        Serial.println(controllerType);
    }
}

Solenoids* InputController::solenoids() {
    return _solenoids;
}

SwitchMatrix* InputController::switchMatrix() {
    return _switchMatrix;
}

LightMatrix* InputController::lightMatrix() {
    return _lightMatrix;
}

PIN2DMD* InputController::pin2Dmd() {
    return _pin2Dmd;
}

PUPComLink* InputController::pupComLink() {
    return _pupComLink;
}

InputControllerTestButtons* InputController::testButtons() {
    return _testButtons;
}

EventDispatcher* InputController::eventDispatcher() {
    return _eventDispatcher;
}
