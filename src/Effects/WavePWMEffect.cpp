#include "WavePWMEffect.h"

void WavePWMEffect::setDevice(EffectDevice* effectDevice) {
    Effect::setDevice(effectDevice);
    wavePWM = (WavePWM*) ((WavePWMDevice *) device)->getWavePWM();
}

void WavePWMEffect::start(int r) {
    Effect::start(r);
    device->on();
    wavePWM->setup(waveDuration);
}

void WavePWMEffect::stop() {
    device->off();
    Effect::stop();
}
