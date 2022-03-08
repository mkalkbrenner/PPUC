/*
  GeneralIlluminationWPC.h.
  Created by Markus Kalkbrenner, 2021.

  Based on Afterglow GI by Christoph Schmid, 2019

  Play more pinball!
*/

#ifndef _GENERALILLUMINATIONWPC_H
#define _GENERALILLUMINATIONWPC_H

/* This code assumes following pin layout:
 *
 *  +----------+---------------+------+
 *  | Name     | Function      | Pin# |
 *  +----------+---------------+------+
 *  | STR1_IN  | D0 Data Bus   | D2   |
 *  | STR2_IN  | D1 Data Bus   | D3   |
 *  | STR3_IN  | D2 Data Bus   | D4   |
 *  | STR4_IN  | D3 Data Bus   | D5   |
 *  | STR5_IN  | D4 Data Bus   | D6   |
 *  | ZC       | Zero Crossing | D12  |
 *  +----------+---------------+------+
*/

// The WPC CPU issues a short signal to turn on the triac controlling the
// AC voltage. The Triac will stay on until the next zero crossing of the
// AC signal.
// The closer the next signal is to the zero crossing, the brighter the lamps
// will be. If no signal is issued at all (stays high), the lamps will light
// at full power (brightness level 8). If the signal remains low, the lamps
// are turned off.
// The zero crossing signal is issued with twice the AC frequency, i.e. with
// 100Hz or every 10ms in Europe.
// The scope says the ZC signal is 1ms long while the Triac signal is only
// ~8us long.

// ZC Sig          TR Sig        ZC Sig          ZC     Zero Crossing Signal
// |                |            |               TR     Triac enable signal
// |--+  |  |  |  | v|  |  |  |  |--+            B0-B6  Brightness 1-7 levels (WPC GI)
// |ZC|                          |ZC|
// |  |B7 B6 B5 B4 B3 B2 B1      |  |
// +-----------------------------+------
// 0ms                           10ms


#include "../EventDispatcher/EventDispatcher.h"

//------------------------------------------------------------------------------
// Setup

// Number of GI strings
#define NUM_GI_STRINGS 5

// Number of brightness steps
#define NUM_BRIGHTNESS 8

// Number of center brightness values required to switch value
#define BRIGHTNESS_SWITCH_THRESH 5

// Brightness interval margin to account for overlapping intervals [us]
#define BRIGHTNESS_INTERVAL_MARGIN 150

// Uncertain brightness value
#define BRIGHTNESS_UNCERTAIN 255

class GeneralIlluminationWPC {
public:
    GeneralIlluminationWPC(EventDispatcher *eD) {
        giInstance = this;
        eventDispatcher = eD;

        pinMode(2, INPUT);
        pinMode(3, INPUT);
        pinMode(4, INPUT);
        pinMode(5, INPUT);
        pinMode(6, INPUT);
        pinMode(12, INPUT_PULLUP); // Inverted on  Adapter.
    }

    void start();
    void stop();
    void update();

    void handlePinChange(uint8_t giString);
    void newBrightness(uint8_t string, uint8_t b);

    static void _changeD0();
    static void _changeD1();
    static void _changeD2();
    static void _changeD3();
    static void _changeD4();
    static void _changeZC();

    volatile uint32_t sZCIntTime = 0;
    volatile uint8_t sInterruptsSeen = 0;
    volatile uint32_t sDataIntLast[NUM_GI_STRINGS] = {0};

protected:
    uint8_t dtToBrightness(uint32_t dt);

    EventDispatcher* eventDispatcher;

    uint8_t sBrightness[NUM_GI_STRINGS] = {0};
    uint8_t sBrightnessTarget[NUM_GI_STRINGS] = {0};
    uint8_t sBrightnessHist[NUM_GI_STRINGS][NUM_BRIGHTNESS + 1]; // including 0 for 'off'

private:
    static GeneralIlluminationWPC *giInstance;
};

#endif //_GENERALILLUMINATIONWPC_H
