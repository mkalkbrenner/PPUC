// Markus Kalkbrenner 2022
// Note to self: Play more pinball!

#include <Arduino.h>

#include "IOBoardController.h"

IOBoardController ioBoardController("0.1.0");

void setup() {
    Serial.begin(9600); // USB is always 12 Mbit/sec

    ioBoardController.eventDispatcher()->addCrossLinkSerial(Serial);
}

void loop() {
    ioBoardController.switches()->update();

    ioBoardController.eventDispatcher()->update();
}
