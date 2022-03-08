#include "SinePWMEffect.h"

void SinePWMEffect::update() {
    uint8_t pwm = 0;

    if (stage == 0) {
        if (ms < (waveDuration / 4)) {
            pwm = rampCompression * wavePWM->getQuadraticValue(ms);
        }
        else {
            stage = 1;
        }
    }

    if (stage == 1) {
        if (ms < duration) {
            pwm = compression * wavePWM->getQuadraticValue(ms) + minIntensity;
        }
        else {
            stage = 2;
        }
    }

    if (stage == 2) {
        pwm = rampCompression * wavePWM->getQuadraticValue(ms);
        if (pwm == 0) {
            stop();
            return;
        }
    }

    // Safety net.
    if (pwm > 255) {
        pwm = 255;
    }

    ((WavePWMDevice *) device)->setPWM(pwm);
}
