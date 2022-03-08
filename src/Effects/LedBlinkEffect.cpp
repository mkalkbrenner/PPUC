#include "LedBlinkEffect.h"

void LedBlinkEffect::update() {
    if (stage == 0) {
        device->off();
        ++stage;
    }
    else if (stage == 1 && ms >= 200) {
        device->on();
        ++stage;
    }
    else if (stage == 2 && ms >= 400) {
        device->off();
        ++stage;
    }
    else if (stage == 3 && ms >= 600) {
        device->on();
        ++stage;
    }
    else if (stage == 4 && ms >= 800) {
        device->off();
        ++stage;
    }
    else if (ms >= 1000) {
        device->on();
        stop();
    }
}
