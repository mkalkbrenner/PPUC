/*
  LedBlinkEffect.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef LedBlinkEffect_h
#define LedBlinkEffect_h

#include <Arduino.h>

#include "Effect.h"

class LedBlinkEffect : public Effect {
public:
    void update();

};

#endif
