#include "WS2812FXDevice.h"

void WS2812FXDevice::on() {
    reset();
    stopped = false;
}

void WS2812FXDevice::off() {
    reset();
    stopped = true;
}

void WS2812FXDevice::reset() {
    ws2812FX->setSegment(firstSegment, firstLED, lastLED, FX_MODE_STATIC, RGBW_BLACK, 1, NO_OPTIONS);
}

WS2812FX* WS2812FXDevice::getWS2812FX() {
    return ws2812FX;
}

int WS2812FXDevice::getFirstLED() {
    return firstLED;
}

int WS2812FXDevice::getlastLED() {
    return lastLED;
}

int WS2812FXDevice::getNumLEDs() {
    return lastLED - firstLED + 1;
}

int WS2812FXDevice::getFirstSegment() {
    return firstSegment;
}

int WS2812FXDevice::getLastSegment() {
    return lastSegment;
}

int WS2812FXDevice::getNumSegments() {
    return lastSegment - firstSegment + 1;
}

bool WS2812FXDevice::isStopped() {
    return stopped;
}

void WS2812FXDevice::setBrightness(byte b) {
    brightness = b;
    ws2812FX->setBrightness(brightness);
}

byte WS2812FXDevice::getBrightness() {
    return brightness;
}

