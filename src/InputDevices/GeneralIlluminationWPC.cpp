//
// Created by Markus Kalkbrenner on 14.03.21.
//

#include "GeneralIlluminationWPC.h"

// see https://forum.arduino.cc/index.php?topic=398610.0
GeneralIlluminationWPC* GeneralIlluminationWPC::giInstance = NULL;

void GeneralIlluminationWPC::start() {
    // initialize data
    for (int i = 0; i < NUM_GI_STRINGS; i++) {
        for (int k = 0; k <= NUM_BRIGHTNESS; k++) {
            sBrightnessHist[i][k] = 0;
        }
    }

    attachInterrupt(digitalPinToInterrupt(2), GeneralIlluminationWPC::_changeD0, RISING);
    attachInterrupt(digitalPinToInterrupt(3), GeneralIlluminationWPC::_changeD1, RISING);
    attachInterrupt(digitalPinToInterrupt(4), GeneralIlluminationWPC::_changeD2, RISING);
    attachInterrupt(digitalPinToInterrupt(5), GeneralIlluminationWPC::_changeD3, RISING);
    attachInterrupt(digitalPinToInterrupt(6), GeneralIlluminationWPC::_changeD4, RISING);
    attachInterrupt(digitalPinToInterrupt(12), GeneralIlluminationWPC::_changeZC, FALLING);
}

void GeneralIlluminationWPC::stop() {
    detachInterrupt(digitalPinToInterrupt(2));
    detachInterrupt(digitalPinToInterrupt(3));
    detachInterrupt(digitalPinToInterrupt(4));
    detachInterrupt(digitalPinToInterrupt(5));
    detachInterrupt(digitalPinToInterrupt(6));
    detachInterrupt(digitalPinToInterrupt(12));
}

void GeneralIlluminationWPC::update() {
    for (int string = 0; string < NUM_GI_STRINGS; string++) {
        if (sBrightness[string] != sBrightnessTarget[string]) {
            sBrightness[string] = sBrightnessTarget[string];
            eventDispatcher->dispatch(new Event(EVENT_SOURCE_GI, word(0, string + 1), sBrightness[string]));
        }
    }
}

void GeneralIlluminationWPC::newBrightness(uint8_t string, uint8_t b) {
    // Check whether the brightness has changed
    if (b <= NUM_BRIGHTNESS && b != sBrightnessTarget[string]) {
        // Add the current brightness value to the histogram
        if (sBrightnessHist[string][b] < 255) {
            sBrightnessHist[string][b]++;
        }

        // Only switch when some measurements in the center of the
        // brightness interval have been seen
        if (sBrightnessHist[string][b] > BRIGHTNESS_SWITCH_THRESH) {
            // switch to the new brightness target value
            sBrightnessTarget[string] = b;

            // clear the histogram
            memset((void*) &(sBrightnessHist[string][0]), 0, NUM_BRIGHTNESS + 1);
        }
    }
}

void GeneralIlluminationWPC::_changeD0() {
    giInstance->handlePinChange(0);
}

void GeneralIlluminationWPC::_changeD1() {
    giInstance->handlePinChange(1);
}

void GeneralIlluminationWPC::_changeD2() {
    giInstance->handlePinChange(2);
}

void GeneralIlluminationWPC::_changeD3() {
    giInstance->handlePinChange(3);
}

void GeneralIlluminationWPC::_changeD4() {
    giInstance->handlePinChange(4);
}

void GeneralIlluminationWPC::handlePinChange(uint8_t giString) {
    // Handle the new brightness value
    newBrightness(giString, dtToBrightness(micros() - sZCIntTime));

    sInterruptsSeen |= (1 << giString);
}

void GeneralIlluminationWPC::_changeZC() {
    //Serial.println("ZC");

    // What time is it?
    giInstance->sZCIntTime = micros();

    // All strings without interrupt in the previous interval are either fully
    // on or off. So their brightness is not set by handlePinChange(). Set
    // 0 (off) or NUM_BRIGHTNESS (on) here.
    for (int i = 0; i < NUM_GI_STRINGS; i++) {
        if ((giInstance->sInterruptsSeen & (1 << i)) == 0) {
            giInstance->newBrightness(i, digitalRead(2 + i) ? 0 : NUM_BRIGHTNESS);
        }
    }
    // Clear the interrupts mask
    giInstance->sInterruptsSeen = 0;
}

uint8_t GeneralIlluminationWPC::dtToBrightness(uint32_t dt)
{
    // This function leaves some margin at the interval borders to account for
    // the fact the intervals are slightly overlapping and therefore an
    // unambiguous brightness determination is not always possible. In this case
    // the function returns 255.
    if (dt < (1200 - BRIGHTNESS_INTERVAL_MARGIN)) {
        // It seems that brightness level 7 is never used in any WPC pinball machine.
        // It us selectable in the GI test, but the time is not measurable.
        // The signal remains HIGH and therefore a brightness level of 8 will be
        // detected. So we return 8 here as well, even if this part of the code
        // should never be reached.
        return NUM_BRIGHTNESS;
    }
    else if ((dt > (1200 + BRIGHTNESS_INTERVAL_MARGIN)) &&
             (dt < (2200 - BRIGHTNESS_INTERVAL_MARGIN)))
    {
        return 6;
    }
    else if ((dt > (2200 + BRIGHTNESS_INTERVAL_MARGIN)) &&
             (dt < (3200 - BRIGHTNESS_INTERVAL_MARGIN)))
    {
        return 5;
    }
    else if ((dt > (3200 + BRIGHTNESS_INTERVAL_MARGIN)) &&
             (dt < (4200 - BRIGHTNESS_INTERVAL_MARGIN)))
    {
        return 4;
    }
    else if ((dt > (4200 + BRIGHTNESS_INTERVAL_MARGIN)) &&
             (dt < (5200 - BRIGHTNESS_INTERVAL_MARGIN)))
    {
        return 3;
    }
    else if ((dt > (5200 + BRIGHTNESS_INTERVAL_MARGIN)) &&
             (dt < (6200 - BRIGHTNESS_INTERVAL_MARGIN)))
    {
        return 2;
    }
    else if ((dt > (6200 + BRIGHTNESS_INTERVAL_MARGIN)) &&
             (dt < (7200 - BRIGHTNESS_INTERVAL_MARGIN)))
    {
        return 1;
    }

    // invalid interval
    return BRIGHTNESS_UNCERTAIN;
}
