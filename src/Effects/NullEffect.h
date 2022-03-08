/*
  NullEffect.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef NULLEFFECT_h
#define NULLEFFECT_h

#include <Arduino.h>

#include "Effect.h"

class NullEffect : public Effect {
public:
    void update();

};

#endif
