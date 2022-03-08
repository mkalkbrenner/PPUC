#include "ImpulsePWMEffect.h"

void ImpulsePWMEffect::update() {
    if (ms > waveDuration) {
        stop();
        return;
    }

    uint8_t pwm = compression * wavePWM->getQuadraticValue(ms);

    // Safety net.
    if (pwm > 255) {
        pwm = 255;
    }

    ((WavePWMDevice *) device)->setPWM(pwm);
}
