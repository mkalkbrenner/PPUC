#include "RampDownStopPWMEffect.h"

void RampDownStopPWMEffect::updateMillis() {
    // Immediately shift to the falling curve of the first period by adding (waveDuration / 2)
    ms = millis() - _ms + (waveDuration / 2);
}

void RampDownStopPWMEffect::update() {
    if (ms > waveDuration) {
        stop();
        return;
    }

    if (stage < 1) {
        maxIntensity = ((WavePWMDevice *) device)->getPWM();
        compression = 255 / maxIntensity;
        stage = 1;
    }

    uint8_t pwm = compression * wavePWM->getQuadraticValue(ms);

    // Safety net.
    if (pwm > 255) {
        pwm = 255;
    }

    ((WavePWMDevice *) device)->setPWM(pwm);
}
