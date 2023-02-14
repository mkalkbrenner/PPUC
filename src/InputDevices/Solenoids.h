/*
  Solenoids.h
  Created by Markus Kalkbrenner, 2020-2021.

  Play more pinball!
*/
#ifndef SOLENOIDS_h
#define SOLENOIDS_h

#define NUM_PINS 26

#include <Arduino.h>

#include "../EventDispatcher/Event.h"
#include "../EventDispatcher/EventDispatcher.h"

class Solenoids {
public:
    //Constructor
    Solenoids(int controllerType, EventDispatcher* eD);

    // WPC
    void registerJ3(byte pin, byte number); // A16100 8-Driver PCB Assembly
    void registerJ4(byte pin, byte number); // A16100 8-Driver PCB Assembly
    void registerJ122(byte pin, byte number);
    void registerJ123(byte pin, byte number);
    void registerJ124(byte pin, byte number);
    void registerJ125(byte pin, byte number);
    void registerJ126(byte pin, byte number);

    // WPC95
    void registerJ110(byte pin, byte number);
    void registerJ111(byte pin, byte number);

    // Sega
    void registerJ9(byte pin, byte number);
    void registerP11(byte pin, byte number);
    void registerP12(byte pin, byte number);

    void update();

    void print();

private:
    EventDispatcher* eventDispatcher;

    int pins[NUM_PINS];
    bool pinStates[NUM_PINS];
    byte previousPinStates[NUM_PINS];

    byte registeredNum[NUM_PINS];
};


#endif
