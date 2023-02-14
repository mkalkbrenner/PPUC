// Markus Kalkbrenner 2022
// Note to self: Play more pinball!

#include <Arduino.h>
#include "InputController.h"
#include "EffectsController.h"

EffectsController effectsController(CONTROLLER_NANO_PIN2DMD_GI, PLATFORM_DATA_EAST);
InputController inputController(CONTROLLER_NANO_PIN2DMD_GI, PLATFORM_DATA_EAST, effectsController.eventDispatcher());

void setup() {
    inputController.pin2Dmd()->setSerial(Serial);
}

void loop() {
    inputController.pin2Dmd()->update();
    inputController.eventDispatcher()->update();
    effectsController.update();
}
