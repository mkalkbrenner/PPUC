#include "WS2812FXEffect.h"

void WS2812FXEffect::setDevice(EffectDevice* effectDevice) {
    Effect::setDevice(effectDevice);
    ws2812FX = (WS2812FX*) ((WS2812FXDevice *) device)->getWS2812FX();
}

void WS2812FXEffect::start(int r) {
    Effect::start();
    device->on();
    ws2812FX->setSegment(getFirstSegment(), getFirstLED(), getlastLED(), mode, colors, speed, options);
    ws2812FX->resetSegmentRuntime(getFirstSegment());
}

void WS2812FXEffect::stop() {
    device->off();
    Effect::stop();
}

void WS2812FXEffect::update() {
    // Don't call service() here!

    if (duration && duration < ms) {
        stop();
    }
}

int WS2812FXEffect::getFirstLED() {
    return ((WS2812FXDevice *) device)->getFirstLED();
}

int WS2812FXEffect::getlastLED() {
    return ((WS2812FXDevice *) device)->getlastLED();
}

int WS2812FXEffect::getNumLEDs() {
    return ((WS2812FXDevice *) device)->getNumLEDs();
}

int WS2812FXEffect::getFirstSegment() {
    return ((WS2812FXDevice *) device)->getFirstSegment();
}

int WS2812FXEffect::getLastSegment() {
    return ((WS2812FXDevice *) device)->getLastSegment();
}

int WS2812FXEffect::getNumSegments() {
    return ((WS2812FXDevice *) device)->getNumSegments();
}
