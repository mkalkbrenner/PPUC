/*
  PwmDevices.h
  Created by Markus Kalkbrenner, 2022.

  Play more pinball!
*/
#ifndef OUTPUT_PwmDevices_h
#define OUTPUT_PwmDevices_h

#include <Arduino.h>

#include "../EventDispatcher/Event.h"
#include "../EventDispatcher/EventDispatcher.h"

#ifndef MAX_PWM_OUTPUTS
#define MAX_PWM_OUTPUTS 16
#endif

class PwmDevices : public EventListener {
public:
    //Constructor
    PwmDevices(EventDispatcher* eD) {
        _eventDispatcher = eD;
        _eventDispatcher->addListener(this, EVENT_SOURCE_LIGHT);
        _eventDispatcher->addListener(this, EVENT_SOURCE_SOLENOID);
        _eventDispatcher->addListener(this, EVENT_SOURCE_SWITCH);
    }

    void registerSolenoid(byte p, byte n, byte pow, byte minPT, byte maxPT, byte hP, byte hPAT, byte fS);
    void registerFlasher(byte p, byte n, byte pow);
    void registerLamp(byte p, byte n, byte pow);

    void update();

    void handleEvent(Event* event);

    void handleEvent(ConfigEvent* event) {}

private:
    unsigned long _ms;

    byte port[MAX_PWM_OUTPUTS] = {0};
    byte number[MAX_PWM_OUTPUTS] = {0};
    byte power[MAX_PWM_OUTPUTS] = {0};
    byte minPulseTime[MAX_PWM_OUTPUTS] = {0};
    byte maxPulseTime[MAX_PWM_OUTPUTS] = {0};
    byte holdPower[MAX_PWM_OUTPUTS] = {0};
    byte holdPowerActivationTime[MAX_PWM_OUTPUTS] = {0};
    byte fastSwitch[MAX_PWM_OUTPUTS] = {0};
    byte type[MAX_PWM_OUTPUTS] = {0};
    unsigned long activated[MAX_PWM_OUTPUTS] = {0};
    bool scheduled[MAX_PWM_OUTPUTS] = {0};
    byte last = 0;

    EventDispatcher* _eventDispatcher;
};

#endif
