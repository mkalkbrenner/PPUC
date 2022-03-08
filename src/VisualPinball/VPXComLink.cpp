#if defined(__IMXRT1062__) // Teensy 4.1
#include <Keyboard.h>
#endif

#include "VPXComLink.h"

void VPXComLink::update() {
    if (Serial.available() >= 5) {
        byte startByte = Serial.read();
        if (startByte == 255) {
            byte sourceId = Serial.read();
            if (sourceId != 0) {
                word eventId = word(Serial.read(), Serial.read());
                if (eventId != 0) {
                    byte value = Serial.read();
                    byte stopByte = Serial.read();
                    if (stopByte == 255) {
                        eventDispatcher->dispatch(new Event((char) sourceId, eventId, value));
                    }
                }
            }
        }
    }
}

void VPXComLink::handleEvent(Event* event) {
    // Add this to platformio.ini to get a Keyboard:
    // build_flags = -D USB_SERIAL_HID
#ifdef Keyboard
    if (event->sourceId == EVENT_SOURCE_SWITCH) {
        if (platform == PLATFORM_SYS11) {
            switch (event->eventId) {
                case 63:
                    if (event->value) {
                        Keyboard.press(KEY_END);
                    } else {
                        Keyboard.release(KEY_END);
                    }
                    break;
                case 64:
                    if (event->value) {
                        Keyboard.press(KEY_PAGE_UP);
                    } else {
                        Keyboard.release(KEY_PAGE_UP);
                    }
                    break;
            }
        }
    }
#endif
}
