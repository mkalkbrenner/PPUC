#include "EventDispatcher.h"

EventDispatcher::EventDispatcher() {
    msg[0] = (byte) 255;
    msg[5] = (byte) 255;
}

// Backward Compatibility, use addCrossLinkSerial().
void EventDispatcher::setCrossLinkSerial(HardwareSerial &reference) {
    crossLink = -1;
    addCrossLinkSerial(reference);
}

void EventDispatcher::addCrossLinkSerial(HardwareSerial &reference) {
    hwSerial[++crossLink] = (HardwareSerial*) &reference;
    hwSerial[crossLink]->begin(115200);
}

void EventDispatcher::addListener(EventListener* eventListener) {
    addListener(eventListener, EVENT_SOURCE_ANY);
}

void EventDispatcher::addListener(EventListener* eventListener, char sourceId) {
    if (numListeners < (MAX_EVENT_LISTENERS - 1)) {
        eventListeners[++numListeners] = eventListener;
        eventListenerFilters[numListeners] = sourceId;
    }
}

void EventDispatcher::dispatch(Event* event) {
    if (stackCounter < (EVENT_STACK_SIZE - 1)) {
        stackEvents[++stackCounter] = event;
    }
    else {
        // Too many events stacked, delete the event and free the memory.
        delete event;
    }
}

void EventDispatcher::callListeners(Event* event, int sender) {
    for (byte i = 0; i <= numListeners; i++) {
        if (event->sourceId == eventListenerFilters[i] || EVENT_SOURCE_ANY == eventListenerFilters[i]) {
            eventListeners[i]->handleEvent(event);
        }
    }

    // Send to other micro controller. But only if there's room left in write buffer. Otherwise the program will be
    // blocked. The buffer gets full if the data is not fetched by the other controller for any reason.
    // @todo Possible optimization to check hwSerial->availableForWrite() >= 6 failed on Arduino for unknown reason.

    if (crossLink != -1 /* && hwSerial->availableForWrite() >= 6 */) {
        //     = (byte) 255;
        msg[1] = (byte) event->sourceId;
        msg[2] = highByte(event->eventId);
        msg[3] = lowByte(event->eventId);
        msg[4] = event->value;
        //     = (byte) 255;

        for (int i = 0; i <= crossLink; i++) {
            if (i != sender) {
                hwSerial[i]->write(msg, 6);
            }
        }
    }

    // delete the event and free the memory
    delete event;
}

void EventDispatcher::update() {
    while (stackCounter >= 0) {
        Event* event = stackEvents[stackCounter--];
        // Integer MAX_CROSS_LINKS is always higher than crossLinks, so this parameters means "no sender, send to all".
        callListeners(event, MAX_CROSS_LINKS);
    }

    for (int i = 0; i <= crossLink; i++) {
        if (hwSerial[i]->available() >= 6) {
            byte startByte = hwSerial[i]->read();
            if (startByte == 255) {
                byte sourceId = hwSerial[i]->read();
                if (sourceId != 0) {
                    word eventId = word(hwSerial[i]->read(), hwSerial[i]->read());
                    if (eventId != 0) {
                        byte value = hwSerial[i]->read();
                        byte stopByte = hwSerial[i]->read();
                        if (stopByte == 255) {
                            callListeners(new Event((char) sourceId, eventId, value), i);
                        }
                    }
                }
            }
        }
    }
}
