/*
  NullDevice.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef NULLDEVICE_h
#define NULLDEVICE_h

#include <Arduino.h>

#include "EffectDevice.h"

class NullDevice : public EffectDevice {
public:

    void on();

    void reset();

};

#endif
