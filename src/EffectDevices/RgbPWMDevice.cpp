#include "RgbStripDevice.h"

void RgbStripDevice::setPWM(uint8_t pwm) {
    setPWMRed(pwm);
    setPWMGreen(pwm);
    setPWMBlue(pwm);

    currentPWM = pwm;
}

void RgbStripDevice::setPWMRed(uint8_t pwm) {
    analogWrite(pin, pwm);
}

void RgbStripDevice::setPWMGreen(uint8_t pwm) {
    analogWrite(pinGreen, pwm);
}

void RgbStripDevice::setPWMBlue(uint8_t pwm) {
    analogWrite(pinBlue, pwm);
}

WavePWM* RgbStripDevice::getWavePWMRed() {
    return wavePWM;
}

WavePWM* RgbStripDevice::getWavePWMGreen() {
    return wavePWMGreen;
}

WavePWM* RgbStripDevice::getWavePWMBlue() {
    return wavePWMBlue;
}
