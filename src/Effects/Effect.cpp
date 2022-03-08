#include "Effect.h"

Effect::Effect() {
}

void Effect::setEventDispatcher(EventDispatcher* eD) {
    eventDispatcher = eD;
}

void Effect::setDevice(EffectDevice* effectDevice) {
    device = effectDevice;
}

void Effect::dispatch(Event* event) {
    eventDispatcher->dispatch(event);
}

bool Effect::isRunning() {
    return running;
}

void Effect::start(int r) {
    //Serial.print("effect started, repeat ");
    //Serial.println(r);

    running = true;
    repeat = r;
    stage = 0;
    ms = 0;
    _ms = millis();
}

void Effect::updateMillis() {
    ms = millis() - _ms;
}

void Effect::resetMillis() {
    ms = 0;
    _ms = millis();
}

void Effect::stop() {
    if (repeat > 0) {
        start(--repeat);
    }
    else if (repeat == -1) {
        start(-1);
    }
    else {
       terminate();
    }
}

void Effect::terminate() {
    running = false;
    stage = 0;
    repeat = 0;
}
