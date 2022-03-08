#include "NullEffect.h"

void NullEffect::update() {
    device->reset();
    stop();
}
