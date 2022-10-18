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

void CrossLinkDebugger::handleEvent(ConfigEvent* event) {
    // On Teensy Serial is the USB Serial.
    Serial.print("handleEvent: ConfigEvent, boardId ");
    Serial.print(event->boardId, DEC);
    Serial.print(", topic ");
    Serial.print(event->topic, DEC);
    Serial.print(", index ");
    Serial.print(event->index, DEC);
    Serial.print(", key ");
    Serial.print(event->key, DEC);
    Serial.print(", value ");
    Serial.println(event->value, HEX);
}
