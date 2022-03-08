/*
  EffectDevice.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef EFFECTDEVICE_h
#define EFFECTDEVICE_h

class EffectDevice {
public:
    virtual void reset() = 0;

    virtual void on() = 0;

    virtual void off();

    virtual ~EffectDevice() {}
};

#endif
