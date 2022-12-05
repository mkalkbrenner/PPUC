// Markus Kalkbrenner 2022
// Note to self: Play more pinball!

#include <Arduino.h>

#include "EffectsController.h"
#include "IOBoardController.h"

IOBoardController ioBoardController("0.1.0");
EffectsController effectsController("0.1.0", PLATFORM_WPC);
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
