#include "CrossLinkDebugger.h"

void CrossLinkDebugger::handleEvent(Event* event) {
    // On Teensy Serial is the USB Serial.
    Serial.print("handleEvent: sourceId ");
    Serial.print(event->sourceId);
    Serial.print(", eventId ");
    Serial.print(event->eventId, DEC);
    Serial.print(", value ");
    Serial.println(event->value, DEC);
}
