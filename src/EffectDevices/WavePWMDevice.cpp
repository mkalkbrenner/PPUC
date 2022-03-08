#include "WavePWMDevice.h"

void WavePWMDevice::on() {
    reset();
}

void WavePWMDevice::reset() {
    setPWM(0);
}

void WavePWMDevice::setPWM(uint8_t pwm) {
    analogWrite(pin, pwm);
    currentPWM = pwm;
}

uint8_t WavePWMDevice::getPWM() {
    return currentPWM;
}

WavePWM* WavePWMDevice::getWavePWM() {
    return wavePWM;
}
