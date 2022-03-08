/*
  EffectsController.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef EFFECTSCONTROLLER_h
#define EFFECTSCONTROLLER_h

#include <Arduino.h>
#include <WS2812Serial.h>
#include <WS2812FX.h>

#include "Effects/Effect.h"
#include "Effects/EffectContainer.h"
#include "EventDispatcher/CrossLinkDebugger.h"
#include "EventDispatcher/Event.h"
#include "EventDispatcher/EventDispatcher.h"
#include "EventDispatcher/EventListener.h"
#include "InputDevices/EffectControllerTestButtons.h"
#include "InputDevices/GeneralIlluminationWPC.h"
#include "EffectDevices/LedBuiltInDevice.h"
#include "EffectDevices/NullDevice.h"
#include "EffectDevices/WavePWMDevice.h"
#include "EffectDevices/WS2812FXDevice.h"
#include "EffectDevices/CombinedGiAndLightMatrixWS2812FXDevice.h"
#include "EffectDevices/RgbStripDevice.h"
#include "Effects/LedBlinkEffect.h"
#include "Effects/NullEffect.h"
#include "Effects/RGBColorCycleEffect.h"
#include "Effects/WS2812FXEffect.h"
#include "Effects/ImpulsePWMEffect.h"
#include "Effects/RampDownStopPWMEffect.h"
#include "Effects/SinePWMEffect.h"

#ifndef EFFECT_STACK_SIZE
#define EFFECT_STACK_SIZE 128
#endif

#define WS2812FX_BRIGHTNESS 64

#define UPDATE_INTERVAL_WS2812FX_EFFECTS 3
#define UPDATE_INTERVAL_WS2812FX_AFTERGLOW 3
#define UPDATE_INTERVAL_WS2812FX_BRIGHTNESS 10

#if defined(PPUC_NUM_LEDS_1) && defined(PPUC_LED_TYPE_1)
    DMAMEM byte frameBuffer1[PPUC_NUM_LEDS_1 * ((PPUC_LED_TYPE_1 < 6) ? 3 : 4) * 4]; // 12 bytes per LED for RGB, 16 bytes for RGBW
#endif

#if defined(PPUC_NUM_LEDS_2) && defined(PPUC_LED_TYPE_2)
    DMAMEM byte frameBuffer2[PPUC_NUM_LEDS_2 * ((PPUC_LED_TYPE_2 < 6) ? 3 : 4) * 4]; // 12 bytes per LED for RGB, 16 bytes for RGBW
#endif

#if defined(PPUC_NUM_LEDS_3) && defined(PPUC_LED_TYPE_3)
    DMAMEM byte frameBuffer3[PPUC_NUM_LEDS_3 * ((PPUC_LED_TYPE_3 < 6) ? 3 : 4) * 4]; // 12 bytes per LED for RGB, 16 bytes for RGBW
#endif

#if defined(PPUC_NUM_LEDS_4) && defined(PPUC_LED_TYPE_4)
    DMAMEM byte frameBuffer4[PPUC_NUM_LEDS_4 * ((PPUC_LED_TYPE_4 < 6) ? 3 : 4) * 4]; // 12 bytes per LED for RGB, 16 bytes for RGBW
#endif

#if defined(PPUC_NUM_LEDS_5) && defined(PPUC_LED_TYPE_5)
    DMAMEM byte frameBuffer5[PPUC_NUM_LEDS_5 * ((PPUC_LED_TYPE_5 < 6) ? 3 : 4) * 4]; // 12 bytes per LED for RGB, 16 bytes for RGBW
#endif

#if defined(PPUC_NUM_LEDS_6) && defined(PPUC_LED_TYPE_6)
    DMAMEM byte frameBuffer6[PPUC_NUM_LEDS_6 * ((PPUC_LED_TYPE_6 < 6) ? 3 : 4) * 4]; // 12 bytes per LED for RGB, 16 bytes for RGBW
#endif

#if defined(PPUC_NUM_LEDS_7) && defined(PPUC_LED_TYPE_7)
    DMAMEM byte frameBuffer7[PPUC_NUM_LEDS_7 * ((PPUC_LED_TYPE_7 < 6) ? 3 : 4) * 4]; // 12 bytes per LED for RGB, 16 bytes for RGBW
#endif

class EffectsController : public EventListener {

public:
    EffectsController(String controllerType, int pinballType) : EventListener(){
        effectsControllerInstance = this;
        _eventDispatcher = new EventDispatcher();
        _eventDispatcher->addListener(this);

        if (controllerType == "0.1.0" || "0.2.0") {
            _ledBuiltInDevice = new LedBuiltInDevice();
            _ledBuiltInDevice->on();
            _nullDevice = new NullDevice();
            _testButtons = new EffectControllerTestButtons(_eventDispatcher);
            _shakerPWMDevice = new WavePWMDevice(36);
            _shakerPWMDevice->off();
            _ledPWMDevice = new WavePWMDevice(37);
            _ledPWMDevice->off();
            if (controllerType != "0.1.0") {
                _rgbStripeDevice = new RgbStripDevice(9, 10, 11);
                _rgbStripeDevice->off();
            }
            else {
                // In revision 0.1.0 these pins are D5-D7, but we don't need them for the WPC GI.
                pinMode(9, INPUT);
                pinMode(10, INPUT);
                pinMode(11, INPUT);
            }
            #if defined(PPUC_NUM_LEDS_1) && defined(PPUC_LED_TYPE_1)
                ws2812FXDevices[0][0] = new WS2812FXDevice(
                    new WS2812FX(PPUC_NUM_LEDS_1, 1, PPUC_LED_TYPE_1),
                    0,
                    PPUC_NUM_LEDS_1 - 1,
                    0,
                    0
                );
                ws2812Serial[0] = new WS2812Serial(PPUC_NUM_LEDS_1, frameBuffer1, ws2812FXDevices[0][0]->getWS2812FX()->getPixels(), 1, PPUC_LED_TYPE_1);
                ws2812Serial[0]->begin();
                ws2812FXDevices[0][0]->getWS2812FX()->init();
                ws2812FXDevices[0][0]->getWS2812FX()->setCustomShow(EffectsController::ws2812SerialShow1);
                // Brightness will be set via potentiometer later.
                ws2812FXDevices[0][0]->setBrightness(WS2812FX_BRIGHTNESS);
                ws2812FXDevices[0][0]->off();
                ws2812FXstates[0] = true;
            #endif
            #if defined(PPUC_NUM_LEDS_2) && defined(PPUC_LED_TYPE_2)
                ws2812FXDevices[1][0] = new WS2812FXDevice(
                    new WS2812FX(PPUC_NUM_LEDS_2, 8, PPUC_LED_TYPE_2),
                    0,
                    PPUC_NUM_LEDS_2 - 1,
                    0,
                    0
                );
                ws2812Serial[1] = new WS2812Serial(PPUC_NUM_LEDS_2, frameBuffer2, ws2812FXDevices[1][0]->getWS2812FX()->getPixels(), 8, PPUC_LED_TYPE_2);
                ws2812Serial[1]->begin();
                ws2812FXDevices[1][0]->getWS2812FX()->init();
                ws2812FXDevices[1][0]->getWS2812FX()->setCustomShow(EffectsController::ws2812SerialShow2);
                // Brightness will be set via potentiometer later.
                ws2812FXDevices[1][0]->setBrightness(WS2812FX_BRIGHTNESS);
                ws2812FXDevices[1][0]->off();
                ws2812FXstates[1] = true;
            #endif
            #if defined(PPUC_NUM_LEDS_3) && defined(PPUC_LED_TYPE_3)
                ws2812FXDevices[2][0] = new WS2812FXDevice(
                    new WS2812FX(PPUC_NUM_LEDS_3, 14, PPUC_LED_TYPE_3),
                    0,
                    PPUC_NUM_LEDS_3 - 1,
                    0,
                    0
                );
                ws2812Serial[2] = new WS2812Serial(PPUC_NUM_LEDS_3, frameBuffer3, ws2812FXDevices[2][0]->getWS2812FX()->getPixels(), 14, PPUC_LED_TYPE_3);
                ws2812Serial[2]->begin();
                ws2812FXDevices[2][0]->getWS2812FX()->init();
                ws2812FXDevices[2][0]->getWS2812FX()->setCustomShow(EffectsController::ws2812SerialShow3);
                // Brightness will be set via potentiometer later.
                ws2812FXDevices[2][0]->setBrightness(WS2812FX_BRIGHTNESS);
                ws2812FXDevices[2][0]->off();
                ws2812FXstates[2] = true;
            #endif
            #if defined(PPUC_NUM_LEDS_4) && defined(PPUC_LED_TYPE_4)
                ws2812FXDevices[3][0] = new WS2812FXDevice(
                    new WS2812FX(PPUC_NUM_LEDS_4, 17, PPUC_LED_TYPE_4),
                    0,
                    PPUC_NUM_LEDS_4 - 1,
                    0,
                    0
                );
                ws2812Serial[3] = new WS2812Serial(PPUC_NUM_LEDS_4, frameBuffer4, ws2812FXDevices[3][0]->getWS2812FX()->getPixels(), 17, PPUC_LED_TYPE_4);
                ws2812Serial[3]->begin();
                ws2812FXDevices[3][0]->getWS2812FX()->init();
                ws2812FXDevices[3][0]->getWS2812FX()->setCustomShow(EffectsController::ws2812SerialShow4);
                // Brightness will be set via potentiometer later.
                ws2812FXDevices[3][0]->setBrightness(WS2812FX_BRIGHTNESS);
                ws2812FXDevices[3][0]->off();
                ws2812FXstates[3] = true;
            #endif
            #if defined(PPUC_NUM_LEDS_5) && defined(PPUC_LED_TYPE_5)
                ws2812FXDevices[4][0] = new WS2812FXDevice(
                    new WS2812FX(PPUC_NUM_LEDS_5, 20, PPUC_LED_TYPE_5),
                    0,
                    PPUC_NUM_LEDS_5 - 1,
                    0,
                    0
                );
                ws2812Serial[4] = new WS2812Serial(PPUC_NUM_LEDS_5, frameBuffer5, ws2812FXDevices[4][0]->getWS2812FX()->getPixels(), 20, PPUC_LED_TYPE_5);
                ws2812Serial[4]->begin();
                ws2812FXDevices[4][0]->getWS2812FX()->init();
                ws2812FXDevices[4][0]->getWS2812FX()->setCustomShow(EffectsController::ws2812SerialShow5);
                // Brightness will be set via potentiometer later.
                ws2812FXDevices[4][0]->setBrightness(WS2812FX_BRIGHTNESS);
                ws2812FXDevices[4][0]->off();
                ws2812FXstates[4] = true;
            #endif
            #if defined(PPUC_NUM_LEDS_6) && defined(PPUC_LED_TYPE_6)
                ws2812FXDevices[5][0] = new WS2812FXDevice(
                    new WS2812FX(PPUC_NUM_LEDS_6, 24, PPUC_LED_TYPE_6),
                    0,
                    PPUC_NUM_LEDS_6 - 1,
                    0,
                    0
                );
                ws2812Serial[5] = new WS2812Serial(PPUC_NUM_LEDS_6, frameBuffer6, ws2812FXDevices[5][0]->getWS2812FX()->getPixels(), 24, PPUC_LED_TYPE_6);
                ws2812Serial[5]->begin();
                ws2812FXDevices[5][0]->getWS2812FX()->init();
                ws2812FXDevices[5][0]->getWS2812FX()->setCustomShow(EffectsController::ws2812SerialShow6);
                // Brightness will be set via potentiometer later.
                ws2812FXDevices[5][0]->setBrightness(WS2812FX_BRIGHTNESS);
                ws2812FXDevices[5][0]->off();
                ws2812FXstates[5] = true;
            #endif
            #if defined(PPUC_NUM_LEDS_7) && defined(PPUC_LED_TYPE_7)
                ws2812FXDevices[6][0] = new WS2812FXDevice(
                    new WS2812FX(PPUC_NUM_LEDS_7, 29, PPUC_LED_TYPE_7),
                    0,
                    PPUC_NUM_LEDS_7 - 1,
                    0,
                    0
                );
                ws2812Serial[6] = new WS2812Serial(PPUC_NUM_LEDS_7, frameBuffer7, ws2812FXDevices[6][0]->getWS2812FX()->getPixels(), 29, PPUC_LED_TYPE_7);
                ws2812Serial[6]->begin();
                ws2812FXDevices[6][0]->getWS2812FX()->init();
                ws2812FXDevices[6][0]->getWS2812FX()->setCustomShow(EffectsController::ws2812SerialShow7);
                // Brightness will be set via potentiometer later.
                ws2812FXDevices[6][0]->setBrightness(WS2812FX_BRIGHTNESS);
                ws2812FXDevices[6][0]->off();
                ws2812FXstates[6] = true;
            #endif
            _testButtons = new EffectControllerTestButtons(_eventDispatcher);

            if (pinballType == PLATFORM_WPC) {
                _generalIllumintationWPC = new GeneralIlluminationWPC(_eventDispatcher);
                _generalIllumintationWPC->start();
            }
        } else {
            Serial.print("Unsupported Effects Controller: ");
            Serial.println(controllerType);
        }
    }

    EventDispatcher* eventDispatcher();

    LedBuiltInDevice* ledBuiltInDevice();

    NullDevice* nullDevice();

    WavePWMDevice* shakerPWMDevice();

    WavePWMDevice* ledPWMDevice();

    RgbStripDevice* rgbStripDevice();

    WS2812FXDevice* ws2812FXDevice(int port);

    CombinedGiAndLightMatrixWS2812FXDevice* createCombinedGiAndLightMatrixWs2812FXDevice(int port);

    CombinedGiAndLightMatrixWS2812FXDevice* giAndLightMatrix(int port);

    WS2812FXDevice* createWS2812FXDevice(int port, int number, int segments, int firstLED, int lastLED);

    WS2812FXDevice* ws2812FXDevice(int port, int number);

    GeneralIlluminationWPC* generalIllumintationWPC();

    void addEffect(Effect* effect, EffectDevice* device, Event* event, int priority, int repeat, int mode);

    //void addEffect(Effect* effect, EffectDevice* device, EventSequence* sequence, int priority, int repeat);

    void addEffect(EffectContainer* container);

    void attachBrightnessControl(byte port, byte poti);

    void setBrightness(byte port, byte brightness);

    void start();

    void update();

    void handleEvent(Event* event);

    static void ws2812SerialShow1() {
        effectsControllerInstance->ws2812Serial[0]->show();
    }
    static void ws2812SerialShow2() {
        effectsControllerInstance->ws2812Serial[1]->show();
    }
    static void ws2812SerialShow3() {
        effectsControllerInstance->ws2812Serial[2]->show();
    }
    static void ws2812SerialShow4() {
        effectsControllerInstance->ws2812Serial[3]->show();
    }
    static void ws2812SerialShow5() {
        effectsControllerInstance->ws2812Serial[4]->show();
    }
    static void ws2812SerialShow6() {
        effectsControllerInstance->ws2812Serial[5]->show();
    }
    static void ws2812SerialShow7() {
        effectsControllerInstance->ws2812Serial[6]->show();
    }

private:
    EventDispatcher* _eventDispatcher;
    LedBuiltInDevice* _ledBuiltInDevice;
    NullDevice* _nullDevice;
    WavePWMDevice* _shakerPWMDevice;
    WavePWMDevice* _ledPWMDevice;
    RgbStripDevice* _rgbStripeDevice;
    WS2812FXDevice* ws2812FXDevices[7][10];
    int ws2812FXDeviceCounters[7] = {1, 1, 1, 1, 1, 1, 1};
    bool ws2812FXstates[7] = {false, false, false, false, false, false, false};
    bool ws2812FXrunning[7] = {false, false, false, false, false, false, false};
    WS2812Serial* ws2812Serial[7];
    EffectContainer* stackEffectContainers[EFFECT_STACK_SIZE];
    int stackCounter = -1;
    byte brightnessControl[7] = {0, 0, 0, 0, 0, 0, 0};
    byte brightnessReads[4] = {0, 0, 0, 0};
    int mode = 0;

    unsigned long ws2812UpdateInterval = 0;
    unsigned long ws2812AfterGlowUpdateInterval = 0;
    unsigned long brightnessUpdateInterval = 0;

    EffectControllerTestButtons* _testButtons;
    GeneralIlluminationWPC* _generalIllumintationWPC;

    static EffectsController* effectsControllerInstance;
};

#endif
