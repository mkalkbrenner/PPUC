#include "PwmDevices.h"

void PwmDevices::registerSolenoid(byte p, byte n, byte pow, byte minPT, byte maxPT, byte hP, byte hPAT, byte fS) {
    if (last < MAX_PWM_OUTPUTS) {
        port[last] = p;
        number[last] = n;
        power[last] = pow;
        minPulseTime[last] = minPT;
        maxPulseTime[last] = maxPT;
        holdPower[last] = hP;
        holdPowerActivationTime[last] = hPAT;
        fastSwitch[last] = fS;

        pinMode(p, OUTPUT);
        analogWrite(p, 0);
        type[last++] = 1;
    }
}

void PwmDevices::registerFlasher(byte p, byte n, byte pow) {
    if (last < MAX_PWM_OUTPUTS) {
        port[last] = p;
        number[last] = n;
        power[last] = pow;

        pinMode(p, OUTPUT);
        analogWrite(p, 0);
        type[last++] = 2;
    }
}

void PwmDevices::registerLamp(byte p, byte n, byte pow) {
    if (last < MAX_PWM_OUTPUTS) {
        port[last] = p;
        number[last] = n;
        power[last] = pow;

        pinMode(p, OUTPUT);
        analogWrite(p, 0);
        type[last++] = 3;
    }
}

void PwmDevices::update() {
    _ms = millis();

    for (byte i = 0; i < last; i++) {
        if (activated[i] > 0) {
            if (
                    (scheduled[i] && ((_ms - activated[i]) > minPulseTime[i])) ||
                    ((maxPulseTime[i] > 0) && ((_ms - activated[i]) > maxPulseTime[i]))
            ) {
                analogWrite(port[i], 0);
                activated[i] = 0;
                scheduled[i] = false;
            }
            else if ((holdPowerActivationTime[i] > 0) && ((_ms - activated[i]) > holdPowerActivationTime[i])) {
                analogWrite(port[i], holdPower[i]);
            }
        }
    }
}

void PwmDevices::handleEvent(Event* event) {
    _ms = millis();

    switch (event->eventId) {
        case EVENT_SOURCE_SOLENOID:
            for (byte i = 0; i < last; i++) {
                if ((type[i] == 1 || type[i] == 2) && number[i] == (byte) event->eventId) {
                    if (event->value && !activated[i]) {
                        analogWrite(port[i], power[i]);
                        activated[i] = _ms;
                    }
                    else if (!event->value && activated[i]) {
                        if (minPulseTime[i] > 0 && (_ms - activated[i]) < minPulseTime[i]) {
                            scheduled[i] = true;
                        }
                        else {
                            analogWrite(port[i], 0);
                            activated[i] = 0;
                        }
                    }
                }
            }
            break;

        case EVENT_SOURCE_SWITCH:
            for (byte i = 0; i < last; i++) {
                if (type[i] == 1 && fastSwitch[i] == (byte) event->eventId) {
                    if (event->value) {
                        analogWrite(port[i], power[i]);
                        activated[i] = _ms;
                    }
                    else if (activated[i]) {
                        analogWrite(port[i], 0);
                        activated[i] = 0;
                        scheduled[i] = false;
                    }
                }
            }
            break;

        case EVENT_SOURCE_LIGHT:
            for (byte i = 0; i < last; i++) {
                if (type[i] == 3 && number[i] == (byte) event->eventId) {
                    if (event->value) {
                        analogWrite(port[i], power[i]);
                    }
                    else if (activated[i]) {
                        analogWrite(port[i], 0);
                    }
                }
            }
            break;
    }
}