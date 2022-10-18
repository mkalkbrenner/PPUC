#include "IOBoardController.h"

IOBoardController::IOBoardController(String controllerType) {
    // Setup RS485 control Pins.
    pinMode(LED_BUILTIN, OUTPUT);

    // Read bordID.
    // @todo draft!
    boardId = (analogRead(17) - 100) / 16 ;

    _eventDispatcher = new EventDispatcher();
    _eventDispatcher->addListener(this, EVENT_CONFIGURATION);

    if (controllerType == "0.1.0") {
        _pwmDevices = new PwmDevices(boardId, _eventDispatcher);
        _switches = new Switches(boardId, _eventDispatcher);
    } else {
        Serial.print("Unsupported Input Controller: ");
        Serial.println(controllerType);
    }
}

void IOBoardController::handleEvent(ConfigEvent* event) {
    if (event->boardId == boardId) {
        switch (event->topic) {
            case CONFIG_TOPIC_SWITCHES:
                switch (event->key) {
                    case CONFIG_TOPIC_PORT:
                        port = event->value;
                        if (number) {
                            _switches->registerSwitch(port, number);
                            port = 0;
                            number = 0;
                        }
                        break;
                    case CONFIG_TOPIC_NUMBER:
                        number = event->value;
                        if (port) {
                            _switches->registerSwitch(port, number);
                            port = 0;
                            number = 0;
                        }
                        break;
                }
                break;
        }
    }
}

PwmDevices* IOBoardController::pwmDevices() {
    return _pwmDevices;
}

Switches* IOBoardController::switches() {
    return _switches;
}

EventDispatcher* IOBoardController::eventDispatcher() {
    return _eventDispatcher;
}

