// Markus Kalkbrenner 2022
// Note to self: Play more pinball!

#include <Arduino.h>

#include "IOBoardController.h"

IOBoardController ioBoardController("0.1.0");

void setup() {
}

void loop() {
    ioBoardController.update();
}
