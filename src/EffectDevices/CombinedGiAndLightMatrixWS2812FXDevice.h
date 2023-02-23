/*
  CombinedGiAndLightMatrixWS2812FXDevice.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

// WPC matrix numbering:
//
//    | C1 | C2 | C3 | C4 | C5 | C6 | C7 | C8
// ---+----+----+----+----+----+----+----+----
// R1 | 11 | 21 | 31 | 41 | 51 | 61 | 71 | 81
// ---+----+----+----+----+----+----+----+----
// R2 | 12 | 22 | 32 | 42 | 52 | 62 | 72 | 82
// ---+----+----+----+----+----+----+----+----
// R3 | 13 | 23 | 33 | 43 | 53 | 63 | 73 | 83
// ---+----+----+----+----+----+----+----+----
// R4 | 14 | 24 | 34 | 44 | 54 | 64 | 74 | 84
// ---+----+----+----+----+----+----+----+----
// R5 | 15 | 25 | 35 | 45 | 55 | 65 | 75 | 85
// ---+----+----+----+----+----+----+----+----
// R6 | 16 | 26 | 36 | 46 | 56 | 66 | 76 | 86
// ---+----+----+----+----+----+----+----+----
// R7 | 17 | 27 | 37 | 47 | 57 | 67 | 77 | 87
// ---+----+----+----+----+----+----+----+----
// R8 | 18 | 28 | 38 | 48 | 58 | 68 | 78 | 88

// DE and SYS11 matrix numbering:
//
//    | C1 | C2 | C3 | C4 | C5 | C6 | C7 | C8
// ---+----+----+----+----+----+----+----+----
// R1 |  1 |  9 | 17 | 25 | 33 | 41 | 49 | 57
// ---+----+----+----+----+----+----+----+----
// R2 |  2 | 10 | 18 | 26 | 34 | 42 | 50 | 58
// ---+----+----+----+----+----+----+----+----
// R3 |  3 | 11 | 19 | 27 | 35 | 43 | 51 | 59
// ---+----+----+----+----+----+----+----+----
// R4 |  4 | 12 | 20 | 28 | 36 | 44 | 52 | 60
// ---+----+----+----+----+----+----+----+----
// R5 |  5 | 13 | 21 | 29 | 37 | 45 | 53 | 61
// ---+----+----+----+----+----+----+----+----
// R6 |  6 | 14 | 22 | 30 | 38 | 46 | 54 | 62
// ---+----+----+----+----+----+----+----+----
// R7 |  7 | 15 | 23 | 31 | 39 | 47 | 55 | 63
// ---+----+----+----+----+----+----+----+----
// R8 |  8 | 16 | 24 | 32 | 40 | 48 | 56 | 64

#ifndef CombinedGiAndLightMatrixWS2812FXDevice_h
#define CombinedGiAndLightMatrixWS2812FXDevice_h

#include <Arduino.h>
#include <WavePWM.h>

#include "WS2812FXDevice.h"
#include "../EventDispatcher/Event.h"
#include "../EventDispatcher/EventListener.h"
#include "../InputDevices/GeneralIlluminationWPC.h"

#define _MAX_LEDS_GI_STRING 50
#define _LIGHT_MATRIX_SIZE 64
#define _MAX_LEDS_PER_LIGHT 3

class CombinedGiAndLightMatrixWS2812FXDevice : public WS2812FXDevice, public EventListener {
public:

    CombinedGiAndLightMatrixWS2812FXDevice(WS2812FX* ws2812FX, int firstLED, int lastLED, int firstSegment, int lastSegment) : WS2812FXDevice(ws2812FX, firstLED, lastLED, firstSegment, lastSegment) {
        wavePWMHeatUp = new WavePWM();
        wavePWMAfterGlow = new WavePWM();
        afterGlowSupport = true;
        for (int number = 0; number < NUM_GI_STRINGS; number++) {
            for (int i = 0; i < _MAX_LEDS_GI_STRING; i++) {
                ledGIPositions[number][i] = -1;
            }
        }
        for (int number = 0; number < _LIGHT_MATRIX_SIZE; number++) {
            for (int i = 0; i < _MAX_LEDS_PER_LIGHT; i++) {
                ledLightMatrixPositions[number][i] = -1;
            }
        }
    }

    void on();
    void off();

    void assignLedToGiString(uint8_t giString, int16_t led);
    void assignLedToGiString(uint8_t giString, int16_t led, uint32_t color);

    void assignLedRangeToGiString(uint8_t giString, int16_t first, int16_t last);

    void assignLedToLightMatrix(uint8_t column, uint8_t row, int16_t led);
    void assignLedToLightMatrix(uint8_t column, uint8_t row, int16_t led, uint32_t color);

    void assignLedToLightMatrixWPC(uint8_t number, int16_t led);
    void assignLedToLightMatrixWPC(uint8_t number, int16_t led, uint32_t color);

    void assignLedToLightMatrixDE(uint8_t number, int16_t led);
    void assignLedToLightMatrixDE(uint8_t number, int16_t led, uint32_t color);

    void assignLedToLightMatrixSYS11(uint8_t number, int16_t led);
    void assignLedToLightMatrixSYS11(uint8_t number, int16_t led, uint32_t color);

    void setDimmedPixelColor(int16_t led, uint32_t color, uint8_t brightness);

    void setHeatUp();
    void setAfterGlow();

    void setHeatUp(int ms);
    void setAfterGlow(int ms);

    void handleEvent(Event* event);
    void handleEvent(ConfigEvent* event) {}
    void updateAfterGlow();

protected:
    int16_t numLEDsGI[NUM_GI_STRINGS] = {0};

    int16_t ledGIPositions[NUM_GI_STRINGS][_MAX_LEDS_GI_STRING] = {{0}};
    uint32_t ledGIColors[NUM_GI_STRINGS][_MAX_LEDS_GI_STRING] = {{0}};
    uint8_t sourceGIBrightness[NUM_GI_STRINGS] = {0};
    uint8_t targetGIBrightness[NUM_GI_STRINGS] = {0};

    // Internally we store the positions in Data East numbering from 1 to 64.
    // The WPC-specific functions convert the WPC-specific numbering.
    int16_t ledLightMatrixPositions[_LIGHT_MATRIX_SIZE][_MAX_LEDS_PER_LIGHT] = {{0}};
    uint32_t ledLightMatrixColors[_LIGHT_MATRIX_SIZE][_MAX_LEDS_PER_LIGHT] = {{0}};

    WavePWM* wavePWMHeatUp;
    WavePWM* wavePWMAfterGlow;

    // When no effects are running, we're in normal GI and Light Matrix mode.
    bool stopped = false; // Never stop the updates.
    bool effectRunning = false;
    bool wpc = false;

    int16_t msHeatUp = 0;
    int16_t msAfterGlow = 0;
    uint32_t heatUpGI[NUM_GI_STRINGS] = {0};
    uint32_t afterGlowGI[NUM_GI_STRINGS] = {0};
    uint32_t heatUp[_LIGHT_MATRIX_SIZE] = {0};
    uint32_t afterGlow[_LIGHT_MATRIX_SIZE] = {0};
};

#endif
