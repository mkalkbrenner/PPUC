#include "PIN2DMD.h"

void PIN2DMD::setSerial(HardwareSerial &reference) {
    hwSerial = (HardwareSerial*) &reference;
    hwSerial->begin(57600);
}

void PIN2DMD::update() {
    if (hwSerial->available() > 2) {
        byte deviceByte = hwSerial->read();
        if (debug) {
            Serial.println(deviceByte, DEC);
        }
        if (deviceByte != 0) {
            byte eventByte = hwSerial->read();
            if (debug) {
                Serial.println(eventByte, DEC);
            }
            if (eventByte != 0) {
                byte nullByte = hwSerial->read();
                if (debug) {
                    Serial.println(nullByte, DEC);
                }
                if (nullByte == 0) {
                    // Quick explanation:
                    // The PUP Player understands event IDs that are 8 bits long. But we assume that nobody needs that
                    // much events. But more than 255, which is the maximum value of 4 bits, are exceeded. The pack for
                    // STTNG is already very close to this limit. On the other hand we don’t really need a device ID as
                    // the  will be the only Device attached to PIN2DMD. But as the device must must not be "0", we
                    // agreed on this pattern:
                    // The „hundreds“ of the decimal Device ID in PIN2DMD are the actual ID. So "100" means Device 1.
                    // ("200" aka Device 2 is not used at the moment and therefore ignored.) The other two digits are
                    // added as high byte to the event ID which itself is treated as low byte.
                    //
                    // Examples of decimal values to be entered in the PIN2DMD Editor:
                    // 100 187 => Device 1, Event 187
                    // 143 187 => Device 1, Event 11195 (43 decimal is 101011 binary, 187 is 10111011, binary 101011 10111011 is 11195 decimal)
                    // 200 123 => Device 2, Event 123   (Device2 is currently not used)
                    // 243 187 => Device 2, Event 11195 (Device2 is currently not used)
                    //
                    // 100 255 =>  Device 1, Event 255
                    // 101 001 =>  Device 1, Event 257
                    //
                    // This looks complicated, but I consider this to be the smartest solution to close the gap between
                    // PIN2DMD 4bit event IDs and PUPPack 8bit event IDs that remains somehow „readable“ in the PIN2DMD
                    // Editor.
                    eventDispatcher->dispatch(new Event(EVENT_SOURCE_DMD, word((deviceByte & B1111111) - 100, eventByte)));
                }
            }
        }
    }
}

void PIN2DMD::setDebug(bool value) {
    debug = value;
}
