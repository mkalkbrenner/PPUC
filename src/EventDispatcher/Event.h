/*
  Event.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef EVENT_h
#define EVENT_h

#define PLATFORM_WPC           1
#define PLATFORM_DATA_EAST     2
#define PLATFORM_SYS11         3

#define EVENT_SOURCE_ANY      42 // "*"
#define EVENT_SOURCE_DEBUG    66 // "B" Debug
#define EVENT_CONFIGURATION   67 // "C" Configure I/O
#define EVENT_SOURCE_DMD      68 // "D" VPX/DOF/PUP
#define EVENT_SOURCE_EVENT    69 // "E" VPX/DOF/PUP common event from different system, like
#define EVENT_SOURCE_EFFECT   70 // "F" custom event from running Effect
#define EVENT_SOURCE_GI       71 // "G" WPC GI
#define EVENT_SOURCE_LIGHT    76 // "L" VPX/DOF/PUP lights, mainly playfield inserts
#define EVENT_NULL            78 // "N" NULL event
#define EVENT_SOURCE_SOUND    79 // "O" sound command
#define EVENT_POLL_EVENTS     80 // "P" Poll events command, mainly read switches
#define EVENT_SOURCE_SOLENOID 83 // "S" VPX/DOF/PUP includes flashers
#define EVENT_SOURCE_SWITCH   87 // "W" VPX/DOF/PUP

struct Event {
    char sourceId;
    word eventId;
    byte value;

    Event(char sId, word eId) {
        sourceId = sId;
        eventId = eId;
        value = 1;
    }

    Event(char sId, word eId, byte v) {
        sourceId = sId;
        eventId = eId;
        value = v;
    }

    bool operator==(const Event &other) const {
        return this->sourceId == other.sourceId
            && this->eventId == other.eventId
            && this->value == other.value;
    }

    bool operator!=(const Event &other) const {
        return !(*this == other);
    }
};

#endif
