#include "RGBColorCycleEffect.h"

void RGBColorCycleEffect::update() {
    WS2812FX* ws2812FX = ((WS2812FXDevice*) device)->getWS2812FX();
    if (stage == 0) {
        color = 0xFF0000;
        device->on();
        ++stage;
    }

    int blue  = color & 255;
    int green = (color >> 8) & 255;
    int red   = (color >> 16) & 255;

    if (ms >= delay) {
        resetMillis();
        if (stage == 1) {
            color = ws2812FX->Color(red, ++green, blue);
            ws2812FX->setColor(color);
            if (color >= 0xFFFF00) {
                ++stage;
            }
        }
        else if (stage == 2) {
            color = ws2812FX->Color(red, green, ++blue);
            ws2812FX->setColor(color);
            if (color >= 0xFFFFFF) {
                ++stage;
            }
        }
        else if (stage == 3) {
            color = ws2812FX->Color(--red, green, blue);
            ws2812FX->setColor(color);
            if (color <= 0x00FFFF) {
                ++stage;
            }
        }
        else if (stage == 4) {
            color = ws2812FX->Color(red, --green, blue);
            ws2812FX->setColor(color);
            if (color <= 0x0000FF) {
                ++stage;
            }
        }
        else if (stage == 5) {
            color = ws2812FX->Color(++red, green, blue);
            ws2812FX->setColor(color);
            if (color >= 0xFF00FF) {
                ++stage;
            }
        }
        else if (stage == 6) {
            color = ws2812FX->Color(red, green, --blue);
            ws2812FX->setColor(color);
            if (color <= 0xFF0000) {
                device->off();
                stop();
            }
        }
    }
}
