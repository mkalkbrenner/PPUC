// Markus Kalkbrenner 2022
// Note to self: Play more pinball!

#include <Arduino.h>
#include <InputController.h>
#include <EventDispatcher/CrossLinkDebugger.h>

InputController inputController("0.1.0", PLATFORM_WPC);

void setup() {
    inputController.pupComLink()->setSerial(Serial);
    inputController.pin2Dmd()->setSerial(Serial1);
    inputController.eventDispatcher()->setCrossLinkSerial(Serial3);

    //inputController.switchMatrix()->setLastColToRead(9);
    inputController.switchMatrix()->registerFieldAsEvent(3, 1, 13); // Start Button
    inputController.switchMatrix()->registerFieldAsEvent(7, 2, 27); // Ball Shooter
    inputController.switchMatrix()->registerFieldAsEvent(8, 2, 28); // Rocket Kicker
    inputController.switchMatrix()->registerFieldAsEvent(1, 3, 31); // Bumper
    inputController.switchMatrix()->registerFieldAsEvent(2, 3, 32); // Bumper
    inputController.switchMatrix()->registerFieldAsEvent(3, 3, 33); // Bumper
    inputController.switchMatrix()->registerFieldAsEvent(1, 6, 61); // Lower Skill
    inputController.switchMatrix()->registerFieldAsEvent(2, 6, 62); // Center Skill
    inputController.switchMatrix()->registerFieldAsEvent(3, 6, 63); // Upper Skill

    inputController.lightMatrix()->registerAllFieldsAsEvent();

    inputController.solenoids()->registerJ125(1, 17); // Flasher Bumpers
    inputController.solenoids()->registerJ125(2, 18); // Flasher Power Payoff
    inputController.solenoids()->registerJ125(3, 19); // Flasher Mini-Playfield
    inputController.solenoids()->registerJ125(5, 20); // Flasher Upper Left Ramp
    inputController.solenoids()->registerJ125(6, 21); // Flasher Left Magnet
    inputController.solenoids()->registerJ125(8, 23); // Flasher Lower Right Magnet
    inputController.solenoids()->registerJ125(9, 24); // Flasher Gumball Motor

    inputController.solenoids()->registerJ124(1, 25); // Left Mini Magnet
    inputController.solenoids()->registerJ124(2, 26); // Right Mini Magnet
    inputController.solenoids()->registerJ124(3, 27); // Left Ramp Diverter
    inputController.solenoids()->registerJ124(5, 28); // Inside Ramp


    inputController.eventDispatcher()->addListener(new CrossLinkDebugger());
    inputController.eventDispatcher()->addListener(inputController.pupComLink(), EVENT_SOURCE_ANY);

    inputController.switchMatrix()->start();
    inputController.lightMatrix()->start();
}

void loop() {
    // read data
    inputController.pin2Dmd()->update();
    inputController.switchMatrix()->update();
    inputController.lightMatrix()->update();
    inputController.solenoids()->update();
    inputController.testButtons()->update();

    // handle data
    inputController.eventDispatcher()->update();
}
