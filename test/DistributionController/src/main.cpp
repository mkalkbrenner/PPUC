// Markus Kalkbrenner 2022
// Note to self: Play more pinball!

#include <Arduino.h>

#include "DistributionController.h"
#include <EventDispatcher/CrossLinkDebugger.h>

DistributionController distributionController("0.1.0", PLATFORM_SYS11);

void setup() {
    Serial.begin(9600); // USB is always 12 Mbit/sec

    distributionController.eventDispatcher()->addCrossLinkSerial(Serial1);
    distributionController.eventDispatcher()->addCrossLinkSerial(Serial2);
    distributionController.eventDispatcher()->addCrossLinkSerial(Serial3);
    distributionController.eventDispatcher()->addCrossLinkSerial(Serial4);
    distributionController.eventDispatcher()->addCrossLinkSerial(Serial5);
    distributionController.eventDispatcher()->addCrossLinkSerial(Serial6);
    distributionController.eventDispatcher()->addCrossLinkSerial(Serial7);
    distributionController.eventDispatcher()->addCrossLinkSerial(Serial8);

    //distributionController.eventDispatcher()->addListener(new PPUCCrossLinkDebugger());
}

void loop() {
    // read data
    distributionController.vpxComLink()->update();
    distributionController.testButtons()->update();

    // handle data
    distributionController.eventDispatcher()->update();
}
