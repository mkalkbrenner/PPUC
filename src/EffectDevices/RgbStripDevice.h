/*
  RgbStripDevice.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef RgbStripDevice_h
#define RgbStripDevice_h

#include <Arduino.h>
#include <WavePWM.h>

#include "WavePWMDevice.h"

class RgbStripDevice : public WavePWMDevice {
public:
    RgbStripDevice(int pinRed, int pinGreen, int pinBlue) : WavePWMDevice(pinRed){
        this->wavePWMGreen = new WavePWM();
        this->wavePWMBlue = new WavePWM();
        this->pinGreen = pinGreen;
        this->pinBlue = pinBlue;
        pinMode(pinGreen, OUTPUT);
        pinMode(pinBlue, OUTPUT);
    }

    void setPWM(uint8_t pwm);

    void setPWMRed(uint8_t pwm);
    void setPWMGreen(uint8_t pwm);
    void setPWMBlue(uint8_t pwm);

    WavePWM* getWavePWMRed();
    WavePWM* getWavePWMGreen();
    WavePWM* getWavePWMBlue();

protected:
    WavePWM* wavePWMGreen;
    WavePWM* wavePWMBlue;

    int pinGreen;
    int pinBlue;
};

#endif
