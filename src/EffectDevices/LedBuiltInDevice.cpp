#include "LedBuiltInDevice.h"

void LedBuiltInDevice::on() {
    digitalWrite(LED_BUILTIN, HIGH);
}

void LedBuiltInDevice::reset() {
    digitalWrite(LED_BUILTIN, LOW);
}
