// Markus Kalkbrenner 2022-2023
// Note to self: Play more pinball!

#include <Arduino.h>

#include "EffectsController.h"
#include "IOBoardController.h"

IOBoardController ioBoardController(CONTROLLER_16_8_1);
EffectsController effectsController(CONTROLLER_16_8_1, PLATFORM_WPC);
MultiCoreCrossLink* multiCoreCrossLink = new MultiCoreCrossLink();

void setup() {
    ioBoardController.eventDispatcher()->setMultiCoreCrossLink(multiCoreCrossLink);
}

void setup1() {
    effectsController.eventDispatcher()->setMultiCoreCrossLink(multiCoreCrossLink);
}

void loop() {
    ioBoardController.update();
}

void loop1() {
    effectsController.update();
}
