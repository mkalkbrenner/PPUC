#include "CombinedGiAndLightMatrixWS2812FXDevice.h"

void CombinedGiAndLightMatrixWS2812FXDevice::on() {
    WS2812FXDevice::on();
    effectRunning = true;
}

void CombinedGiAndLightMatrixWS2812FXDevice::off() {
    effectRunning = false;
    // No stop. Just reset to quit effects and return to standard GI and Light Matrix operation.
    reset();
}

void CombinedGiAndLightMatrixWS2812FXDevice::assignLedToGiString(uint8_t giString, int8_t led) {
    assignLedToGiString(giString, led, ULTRAWHITE);
}

void CombinedGiAndLightMatrixWS2812FXDevice::assignLedToGiString(uint8_t giString, int8_t led, uint32_t color) {
    if (numLEDsGI[--giString] < _MAX_LEDS_GI_STRING) {
        ledGIPositions[giString][numLEDsGI[giString]] = led;
        ledGIColors[giString][numLEDsGI[giString]++] = color;
    }
}

void CombinedGiAndLightMatrixWS2812FXDevice::assignLedToLightMatrix(uint8_t column, uint8_t row, int8_t led) {
    assignLedToLightMatrix(column, row, led, ULTRAWHITE);
}

void CombinedGiAndLightMatrixWS2812FXDevice::assignLedToLightMatrix(uint8_t column, uint8_t row, int8_t led, uint32_t color) {
    assignLedToLightMatrixDE(((column - 1) * 8) + row , led, color);
}

void CombinedGiAndLightMatrixWS2812FXDevice::assignLedToLightMatrixWPC(uint8_t number, int8_t led) {
    assignLedToLightMatrixWPC(number, led, ULTRAWHITE);
    wpc = true;
}

void CombinedGiAndLightMatrixWS2812FXDevice::assignLedToLightMatrixWPC(uint8_t number, int8_t led, uint32_t color) {
    assignLedToLightMatrix(number / 10 % 10, number % 10, led, color);
    wpc = true;
}

void CombinedGiAndLightMatrixWS2812FXDevice::assignLedToLightMatrixSYS11(uint8_t number, int8_t led) {
    assignLedToLightMatrixDE(number, led, ULTRAWHITE);
}

void CombinedGiAndLightMatrixWS2812FXDevice::assignLedToLightMatrixSYS11(uint8_t number, int8_t led, uint32_t color) {
    assignLedToLightMatrixDE(number, led, color);
}

void CombinedGiAndLightMatrixWS2812FXDevice::assignLedToLightMatrixDE(uint8_t number, int8_t led) {
    assignLedToLightMatrixDE(number, led, ULTRAWHITE);
}

void CombinedGiAndLightMatrixWS2812FXDevice::assignLedToLightMatrixDE(uint8_t number, int8_t led, uint32_t color) {
    --number;
    for (int i = 0; i < _MAX_LEDS_PER_LIGHT; i++) {
        if (ledLightMatrixPositions[number][i] == -1) {
            ledLightMatrixPositions[number][i] = led;
            ledLightMatrixColors[number][i] = color;
            break;
        }
    }
}

void CombinedGiAndLightMatrixWS2812FXDevice::handleEvent(Event* event) {
    if (!effectRunning) {
        if (event->sourceId == EVENT_SOURCE_GI) {
            uint8_t giString = event->eventId - 1;
            // Brightness is a value between 0 and 8. Convert it into a value from 0 to 255.
            uint8_t giBrightness = 0;
            switch (event->value) {
                case 1:
                    giBrightness = 35;
                    break;
                case 2:
                    giBrightness = 60;
                    break;
                case 3:
                    giBrightness = 85;
                    break;
                case 4:
                    giBrightness = 115;
                    break;
                case 5:
                    giBrightness = 155;
                    break;
                case 6:
                    giBrightness = 205;
                    break;
                case 7:
                case 8:
                    giBrightness = 255;
                    break;
            }

            if (targetGIBrightness[giString] != giBrightness) {
                if (
                        (targetGIBrightness[giString] < giBrightness && msHeatUp == 0) ||
                        (targetGIBrightness[giString] > giBrightness && msAfterGlow == 0)
                ) {
                    for (int i = 0; i <= numLEDsGI[giString]; i++) {
                        setDimmedPixelColor(ledGIPositions[giString][i], ledGIColors[giString][i], giBrightness);
                    }
                }
                else {
                    if (targetGIBrightness[giString] < giBrightness) {
                        if (heatUpGI[giString] == 0 && afterGlowGI[giString] == 0) {
                            heatUpGI[giString] = millis();
                        } else if (afterGlowGI[giString] > 0) {
                            // There's still an after glow effect running. Start heat up from current value.
                            byte value = wavePWMAfterGlow->getExponentialValue(millis() - afterGlowGI[giString] + msAfterGlow);
                            afterGlowGI[giString] = 0;
                            for (int ms = 1; ms <= msHeatUp; ms++) {
                                if (wavePWMHeatUp->getExponentialValue(ms) >= value) {
                                    heatUpGI[giString] = millis() - ms;
                                    break;
                                }
                            }
                            // safety net
                            if (heatUpGI[giString] == 0) {
                                heatUpGI[giString] = millis() - msHeatUp + 1;
                            }
                        }
                    } else {
                        if (afterGlowGI[giString] == 0 && heatUpGI[giString] == 0) {
                            afterGlowGI[giString] = millis();
                        } else if (heatUpGI[giString] > 0) {
                            // There's still a heat up effect running. Start after glow from current value.
                            byte value = wavePWMHeatUp->getExponentialValue(millis() - heatUp[giString]);
                            heatUpGI[giString] = 0;
                            for (int ms = msAfterGlow; ms <= (msAfterGlow * 2); ms++) {
                                if (wavePWMAfterGlow->getExponentialValue(ms) <= value) {
                                    afterGlowGI[giString] = millis() - ms;
                                    break;
                                }
                            }
                            // safety net
                            if (afterGlowGI[giString] == 0) {
                                afterGlowGI[giString] = millis() - (2 * msAfterGlow) + 1;
                            }
                        }
                    }
                }

                sourceGIBrightness[giString] = targetGIBrightness[giString];
                targetGIBrightness[giString] = giBrightness;
            }
        }
        else if (event->sourceId == EVENT_SOURCE_LIGHT) {
            //char system = (event->eventId & 0xFF00) >> 8;
            //uint8_t number = event->eventId & 0x00FF;

            uint8_t number = event->eventId;

            if (wpc) {
                // WPC
                uint8_t column = number / 10 % 10;
                uint8_t row = number % 10;
                number = ((column - 1) * 8) + row;
            }

            --number;
            bool on = (bool) event->value;

            for (int i = 0; i < _MAX_LEDS_PER_LIGHT; i++) {
                if (ledLightMatrixPositions[number][i] >= 0) {
                    if (on && msHeatUp == 0) {
                        ws2812FX->setPixelColor(ledLightMatrixPositions[number][i], ledLightMatrixColors[number][i]);
                    }
                    else if (!on && msAfterGlow == 0) {
                        ws2812FX->setPixelColor(ledLightMatrixPositions[number][i], RGBW_BLACK);
                    }
                    else if (i == 0) {
                        if (on) {
                            if (heatUp[number] == 0 && afterGlow[number] == 0) {
                                heatUp[number] = millis();
                            } else if (afterGlow[number] > 0) {
                                // There's still an after glow effect running. Start heat up from current value.
                                byte value = wavePWMAfterGlow->getExponentialValue(millis() - afterGlow[number] + msAfterGlow);
                                afterGlow[number] = 0;
                                for (int ms = 1; ms <= msHeatUp; ms++) {
                                    if (wavePWMHeatUp->getExponentialValue(ms) >= value) {
                                        heatUp[number] = millis() - ms;
                                        break;
                                    }
                                }
                                // safety net
                                if (heatUp[number] == 0) {
                                    heatUp[number] = millis() - msHeatUp + 1;
                                }
                            }
                        } else {
                            if (afterGlow[number] == 0 && heatUp[number] == 0) {
                                afterGlow[number] = millis();
                            } else if (heatUp[number] > 0) {
                                // There's still a heat up effect running. Start after glow from current value.
                                byte value = wavePWMHeatUp->getExponentialValue(millis() - heatUp[number]);
                                heatUp[number] = 0;
                                for (int ms = msAfterGlow; ms <= (msAfterGlow * 2); ms++) {
                                    if (wavePWMAfterGlow->getExponentialValue(ms) <= value) {
                                        afterGlow[number] = millis() - ms;
                                        break;
                                    }
                                }
                                // safety net
                                if (afterGlow[number] == 0) {
                                    afterGlow[number] = millis() - (2 * msAfterGlow) + 1;
                                }
                            }
                        }

                        // terminate the loop
                        return;
                    }
                }
            }
        }
    }
}

void CombinedGiAndLightMatrixWS2812FXDevice::updateAfterGlow() {
    for (uint8_t giString = 0; giString < NUM_GI_STRINGS; giString++) {
        uint8_t glowBrightness = targetGIBrightness[giString];
        if (heatUpGI[giString] > 0) {
            if ((millis() - heatUpGI[giString]) >= msHeatUp) {
                heatUpGI[giString] = 0;
            }
            else {
                float diff = targetGIBrightness[giString] - sourceGIBrightness[giString];
                float mult = diff / 255;
                glowBrightness = sourceGIBrightness[giString] + (wavePWMHeatUp->getExponentialValue(millis() - heatUpGI[giString]) * mult);
            }
        }
        else if (afterGlowGI[giString] > 0) {
            if ((millis() - afterGlowGI[giString]) >= msAfterGlow) {
                afterGlowGI[giString] = 0;
            }
            else {
                float diff = sourceGIBrightness[giString] - targetGIBrightness[giString];
                float mult = diff / 255;
                glowBrightness = targetGIBrightness[giString] + (wavePWMAfterGlow->getExponentialValue(millis() - afterGlowGI[giString] + msAfterGlow) * mult);
             }
        }
        else {
            continue;
        }

        for (int i = 0; i < numLEDsGI[giString]; i++) {
            if (ledGIPositions[giString][i] != -1) {
                setDimmedPixelColor(ledGIPositions[giString][i], ledGIColors[giString][i], glowBrightness);
            }
        }
    }

    for (uint8_t number = 0; number < _LIGHT_MATRIX_SIZE; number++) {
        uint8_t glowBrightness;
        if (heatUp[number] > 0) {
            if ((millis() - heatUp[number]) >= msHeatUp) {
                heatUp[number] = 0;
                for (int i = 0; i < _MAX_LEDS_PER_LIGHT; i++) {
                    if (ledLightMatrixPositions[number][i] != -1) {
                        ws2812FX->setPixelColor(ledLightMatrixPositions[number][i], ledLightMatrixColors[number][i]);
                    }
                }
            }
            else {
                glowBrightness = wavePWMHeatUp->getExponentialValue(millis() - heatUp[number]);
            }
        }
        else if (afterGlow[number] > 0) {
            if ((millis() - afterGlow[number]) >= msAfterGlow) {
                afterGlow[number] = 0;
                for (int i = 0; i < _MAX_LEDS_PER_LIGHT; i++) {
                    if (ledLightMatrixPositions[number][i] != -1) {
                        ws2812FX->setPixelColor(ledLightMatrixPositions[number][i], RGBW_BLACK);
                    }
                }
            }
            else {
                glowBrightness = wavePWMAfterGlow->getExponentialValue(millis() - afterGlow[number] + msAfterGlow);
            }
        }

        if (heatUp[number] > 0 || afterGlow[number] > 0) {
            for (int i = 0; i < _MAX_LEDS_PER_LIGHT; i++) {
                if (ledLightMatrixPositions[number][i] != -1) {
                    setDimmedPixelColor(ledLightMatrixPositions[number][i], ledLightMatrixColors[number][i], glowBrightness);
                }
            }
        }
    }
}

void CombinedGiAndLightMatrixWS2812FXDevice::setDimmedPixelColor(int led, uint32_t color, uint8_t brightness) {
    uint8_t w = (color >> 24) & 0xFF;
    uint8_t r = (color >> 16) & 0xFF;
    uint8_t g = (color >> 8) & 0xFF;
    uint8_t b = color & 0xFF;

    // uint32_t for more space during the operation
    uint32_t mult = brightness + 1;
    b = (b * mult) >> 8;
    g = (g * mult) >> 8;
    r = (r * mult) >> 8;
    w = (w * mult) >> 8;

    ws2812FX->setPixelColor(led, r, g, b, w);
}

void CombinedGiAndLightMatrixWS2812FXDevice::setHeatUp() {
    setHeatUp(30);
}

void CombinedGiAndLightMatrixWS2812FXDevice::setAfterGlow() {
    setAfterGlow(400);
}

void CombinedGiAndLightMatrixWS2812FXDevice::setHeatUp(int ms) {
    wavePWMHeatUp->setup(ms * 2);
    msHeatUp = ms;
}

void CombinedGiAndLightMatrixWS2812FXDevice::setAfterGlow(int ms) {
    wavePWMAfterGlow->setup(ms * 2);
    msAfterGlow = ms;
}
