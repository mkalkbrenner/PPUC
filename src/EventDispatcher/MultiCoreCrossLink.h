#ifndef MULTI_CORE_CROSS_LINK_h
#define MULTI_CORE_CROSS_LINK_h

#if defined(ARDUINO_ARCH_MBED_RP2040) || defined(ARDUINO_ARCH_RP2040)
#include <pico/util/queue.h>
#endif

#include "Event.h"

#ifndef EVENT_STACK_SIZE
#define EVENT_STACK_SIZE 100
#endif

class MultiCoreCrossLink {
#if defined(ARDUINO_ARCH_MBED_RP2040) || defined(ARDUINO_ARCH_RP2040)
public:
    MultiCoreCrossLink() {
        queue_init(&_eventQueue[0], sizeof(Event), EVENT_STACK_SIZE);
        queue_init(&_eventQueue[1], sizeof(Event), EVENT_STACK_SIZE);
        queue_init(&_configEventQueue, sizeof(ConfigEvent), EVENT_STACK_SIZE);
    }

    ~MultiCoreCrossLink() { /* noop */ };

    void pushEvent(Event* event) {
        while (!pushEventNonBlocking(event)) { /* noop */ }
    }

    bool pushEventNonBlocking(Event* event) {
        return queue_try_add(&_eventQueue[get_core_num() ^ 1], new Event(event));
    }

    Event* popEvent() {
        Event* event;
        while (!popEventNonBlocking(event)) { /* noop */ }
        return event;
    }

    bool popEventNonBlocking(Event* event) {
        return queue_try_remove(&_eventQueue[get_core_num()], event);
    }

    int eventAvailable() {
        return queue_get_level(&_eventQueue[get_core_num()]);
    }

    void pushConfigEvent(ConfigEvent* event) {
        if (get_core_num() == 0) {
            while (!pushConfigEventNonBlocking(event)) { /* noop */ }
        }
    }

    bool pushConfigEventNonBlocking(ConfigEvent* event) {
        if (get_core_num() == 0) {
            return queue_try_add(&_configEventQueue, new ConfigEvent(event));
        }

        return false;
    }

    ConfigEvent* popConfigEvent() {
        ConfigEvent* event;
        while (!popConfigEventNonBlocking(event)) { /* noop */ }
        return event;
    }

    bool popConfigEventNonBlocking(ConfigEvent* event) {
        return get_core_num() == 1 && queue_try_remove(&_configEventQueue, event);
    }

    int configEventAvailable() {
        return get_core_num() == 1 && queue_get_level(&_configEventQueue);
    }

private:
    queue_t _eventQueue[2];
    queue_t _configEventQueue;
#endif
};

#endif