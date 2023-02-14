#include "Solenoids.h"

Solenoids::Solenoids(int controllerType, EventDispatcher* ed) {
    eventDispatcher = ed;

    if (controllerType == CONTROLLER_MEGA_ALL_INPUT || controllerType == CONTROLLER_MEGA_ALL_INPUT_2) {
        pins[0] = 8;
        pins[1] = 9;
        pins[2] = 10;
        pins[3] = 11;
        pins[4] = 12;
        pins[5] = 13;
        pins[6] = 30;
        pins[7] = 31;
        pins[8] = 32;
        pins[9] = 33;
        pins[10] = 34;
        pins[11] = 35;
        pins[12] = 36;
        pins[13] = 37;
        pins[14] = 38;
        pins[15] = 39;
        pins[16] = 40;
        pins[17] = 41;
        pins[18] = 42;
        pins[19] = 43;
        pins[20] = 44;
        pins[21] = 45;
        pins[22] = 46;
        pins[23] = 47;
        pins[24] = 48;
        pins[25] = 49;
    }

    for (int i = 0; i < NUM_PINS; i++) {
        pinMode(pins[i], INPUT);
        pinStates[i] = false;
        previousPinStates[i] = false;
        registeredNum[i] = 0;
    }
}

void Solenoids::update() {
    for (int i = 0; i < NUM_PINS; i++) {
        previousPinStates[i] = pinStates[i];
        pinStates[i] = digitalRead(pins[i]) == HIGH;
        if ((registeredNum[i] != 0) && (previousPinStates[i] != pinStates[i])) {
            eventDispatcher->dispatch(new Event(EVENT_SOURCE_SOLENOID, word(0, registeredNum[i]), pinStates[i]));
        }
    }
}

void Solenoids::registerJ3(byte pin, byte number) {
    if      (pin == 1) { registeredNum[0] = number; }
    else if (pin == 2) { registeredNum[1] = number; }
    else if (pin == 3) { registeredNum[2] = number; }
    else if (pin == 4) { registeredNum[3] = number; }
    else if (pin == 5) { registeredNum[4] = number; }
    // 6 is key
    else if (pin == 7) { registeredNum[5] = number; }
}

void Solenoids::registerJ4(byte pin, byte number) {
    if      (pin == 1) { registeredNum[0] = number; }
    else if (pin == 2) { registeredNum[1] = number; }
    // 3 is key
    else if (pin == 4) { registeredNum[3] = number; }
    else if (pin == 5) { registeredNum[4] = number; }
    else if (pin == 6) { registeredNum[2] = number; }
    else if (pin == 7) { registeredNum[5] = number; }
}

void Solenoids::registerJ122(byte pin, byte number) {
    if      (pin == 1) { registeredNum[6] = number; }
    else if (pin == 2) { registeredNum[7] = number; }
    else if (pin == 3) { registeredNum[8] = number; }
    else if (pin == 4) { registeredNum[9] = number; }
    else if (pin == 5) { registeredNum[10] = number; }
    else if (pin == 6) { registeredNum[11] = number; }
    // 7 is key
    else if (pin == 8) { registeredNum[12] = number; }
    else if (pin == 9) { registeredNum[13] = number; }
}

void Solenoids::registerJ123(byte pin, byte number) {
    if      (pin == 1) { registeredNum[6] = number; }
    // 2 is key
    else if (pin == 3) { registeredNum[7] = number; }
    else if (pin == 4) { registeredNum[8] = number; }
    else if (pin == 5) { registeredNum[9] = number; }
}

void Solenoids::registerJ124(byte pin, byte number) {
    if      (pin == 1) { registeredNum[6] = number; }
    else if (pin == 2) { registeredNum[7] = number; }
    else if (pin == 3) { registeredNum[8] = number; }
    // 4 is key
    else if (pin == 5) { registeredNum[9] = number; }
}


void Solenoids::registerJ125(byte pin, byte number) {
    if      (pin == 1) { registeredNum[14] = number; }
    else if (pin == 2) { registeredNum[15] = number; }
    else if (pin == 3) { registeredNum[16] = number; }
    // 4 is key
    else if (pin == 5) { registeredNum[17] = number; }
    else if (pin == 6) { registeredNum[18] = number; }
    else if (pin == 7) { registeredNum[19] = number; }
    else if (pin == 8) { registeredNum[20] = number; }
    else if (pin == 9) { registeredNum[21] = number; }
}

void Solenoids::registerJ126(byte pin, byte number) {
    if      (pin == 1)  { registeredNum[14] = number; }
    else if (pin == 2)  { registeredNum[15] = number; }
    else if (pin == 3)  { registeredNum[16] = number; }
    else if (pin == 4)  { registeredNum[17] = number; }
    else if (pin == 5)  { registeredNum[18] = number; }
    else if (pin == 6)  { registeredNum[19] = number; }
    else if (pin == 7)  { registeredNum[20] = number; }
    else if (pin == 8)  { registeredNum[21] = number; }
    // 9 is key
    else if (pin == 10) { registeredNum[22] = number; }
    else if (pin == 11) { registeredNum[23] = number; }
    else if (pin == 12) { registeredNum[24] = number; }
    else if (pin == 13) { registeredNum[25] = number; }
}

void Solenoids::registerJ110(byte pin, byte number) {
}

void Solenoids::registerJ111(byte pin, byte number) {
}

void Solenoids::registerJ9(byte pin, byte number) {
}

void Solenoids::registerP11(byte pin, byte number) {
}

void Solenoids::registerP12(byte pin, byte number) {
}

//helps with debugging
void Solenoids::print() {
	for (int i = 0; i < NUM_PINS; i++) {
		Serial.print(pinStates[i]);
		Serial.print(" ");
	}
	Serial.println();
}
