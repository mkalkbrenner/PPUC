/*
  EffectsController.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef EFFECTSCONTROLLER_h
#define EFFECTSCONTROLLER_h

#include "PPUC.h"
#if defined(__IMXRT1062__) // Teensy 4.1
    #include <WS2812Serial.h>
#else
    #include <Adafruit_NeoPixel.h>
#endif
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

#if PPUC_CONTROLLER == CONTROLLER_TEENSY_OUTPUT
    #define PPUC_MAX_WS2812FX_DEVICES 7
    #define PPUC_MAX_BRIGHTNESS_CONTROLS 4
#else
    #define PPUC_MAX_WS2812FX_DEVICES 1
    #define PPUC_MAX_BRIGHTNESS_CONTROLS 1
#endif

#if defined(PPUC_NUM_LEDS_1) && defined(PPUC_LED_TYPE_1) && defined(__IMXRT1062__)
    DMAMEM byte frameBuffer1[PPUC_NUM_LEDS_1 * ((PPUC_LED_TYPE_1 < 6) ? 3 : 4) * 4]; // 12 bytes per LED for RGB, 16 bytes for RGBW
#endif

#if defined(PPUC_NUM_LEDS_2) && defined(PPUC_LED_TYPE_2) && defined(__IMXRT1062__)
    DMAMEM byte frameBuffer2[PPUC_NUM_LEDS_2 * ((PPUC_LED_TYPE_2 < 6) ? 3 : 4) * 4]; // 12 bytes per LED for RGB, 16 bytes for RGBW
#endif

#if defined(PPUC_NUM_LEDS_3) && defined(PPUC_LED_TYPE_3) && defined(__IMXRT1062__)
    DMAMEM byte frameBuffer3[PPUC_NUM_LEDS_3 * ((PPUC_LED_TYPE_3 < 6) ? 3 : 4) * 4]; // 12 bytes per LED for RGB, 16 bytes for RGBW
#endif

#if defined(PPUC_NUM_LEDS_4) && defined(PPUC_LED_TYPE_4) && defined(__IMXRT1062__)
    DMAMEM byte frameBuffer4[PPUC_NUM_LEDS_4 * ((PPUC_LED_TYPE_4 < 6) ? 3 : 4) * 4]; // 12 bytes per LED for RGB, 16 bytes for RGBW
#endif

#if defined(PPUC_NUM_LEDS_5) && defined(PPUC_LED_TYPE_5) && defined(__IMXRT1062__)
    DMAMEM byte frameBuffer5[PPUC_NUM_LEDS_5 * ((PPUC_LED_TYPE_5 < 6) ? 3 : 4) * 4]; // 12 bytes per LED for RGB, 16 bytes for RGBW
#endif

#if defined(PPUC_NUM_LEDS_6) && defined(PPUC_LED_TYPE_6) && defined(__IMXRT1062__)
    DMAMEM byte frameBuffer6[PPUC_NUM_LEDS_6 * ((PPUC_LED_TYPE_6 < 6) ? 3 : 4) * 4]; // 12 bytes per LED for RGB, 16 bytes for RGBW
#endif

#if defined(PPUC_NUM_LEDS_7) && defined(PPUC_LED_TYPE_7) && defined(__IMXRT1062__)
    DMAMEM byte frameBuffer7[PPUC_NUM_LEDS_7 * ((PPUC_LED_TYPE_7 < 6) ? 3 : 4) * 4]; // 12 bytes per LED for RGB, 16 bytes for RGBW
#endif

class EffectsController : public EventListener {

public:
    EffectsController(int ct, int pf) : EventListener(){
        controllerType = ct;
        platform = pf;

        effectsControllerInstance = this;
        _eventDispatcher = new EventDispatcher();
        _eventDispatcher->addListener(this);

        if (controllerType == CONTROLLER_TEENSY_OUTPUT) {
            _ledBuiltInDevice = new LedBuiltInDevice();
            _ledBuiltInDevice->on();
            _nullDevice = new NullDevice();
            _testButtons = new EffectControllerTestButtons(_eventDispatcher);
            _shakerPWMDevice = new WavePWMDevice(36);
            _shakerPWMDevice->off();
            _ledPWMDevice = new WavePWMDevice(37);
            _ledPWMDevice->off();
            if (controllerType != CONTROLLER_TEENSY_OUTPUT) {
                _rgbStripeDevice = new RgbStripDevice(9, 10, 11);
                _rgbStripeDevice->off();
            }
            else {
                // In revision 0.1.0 these pins are D5-D7, but we don't need them for the WPC GI.
                pinMode(9, INPUT);
                pinMode(10, INPUT);
                pinMode(11, INPUT);
            }

            brightnessControlBasePin = 38;

            #if defined(PPUC_NUM_LEDS_1) && defined(PPUC_LED_TYPE_1)
                ws2812FXDevices[0][0] = new WS2812FXDevice(
                    new WS2812FX(PPUC_NUM_LEDS_1, 1, PPUC_LED_TYPE_1),
                    0,
                    PPUC_NUM_LEDS_1 - 1,
                    0,
                    0
                );
                ws2812FXDevices[0][0]->getWS2812FX()->init();
                ws2812FXDeviceCounters[0] = 1;

                #if defined(__IMXRT1062__) // Teensy 4.1
                    ws2812Serial[0] = new WS2812Serial(PPUC_NUM_LEDS_1, frameBuffer1, ws2812FXDevices[0][0]->getWS2812FX()->getPixels(), 1, PPUC_LED_TYPE_1);
                    ws2812Serial[0]->begin();
                    ws2812FXDevices[0][0]->getWS2812FX()->setCustomShow(EffectsController::ws2812SerialShow1);
                #endif

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
                ws2812FXDevices[1][0]->getWS2812FX()->init();
                ws2812FXDeviceCounters[1] = 1;

                #if defined(__IMXRT1062__) // Teensy 4.1
                    ws2812Serial[1] = new WS2812Serial(PPUC_NUM_LEDS_2, frameBuffer2, ws2812FXDevices[1][0]->getWS2812FX()->getPixels(), 8, PPUC_LED_TYPE_2);
                    ws2812Serial[1]->begin();
                    ws2812FXDevices[1][0]->getWS2812FX()->setCustomShow(EffectsController::ws2812SerialShow2);
                #endif

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
                ws2812FXDevices[2][0]->getWS2812FX()->init();
                ws2812FXDeviceCounters[2] = 1;

                #if defined(__IMXRT1062__) // Teensy 4.1
                    ws2812Serial[2] = new WS2812Serial(PPUC_NUM_LEDS_3, frameBuffer3, ws2812FXDevices[2][0]->getWS2812FX()->getPixels(), 14, PPUC_LED_TYPE_3);
                    ws2812Serial[2]->begin();
                    ws2812FXDevices[2][0]->getWS2812FX()->setCustomShow(EffectsController::ws2812SerialShow3);
                #endif

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
                ws2812FXDevices[3][0]->getWS2812FX()->init();
                ws2812FXDeviceCounters[3] = 1;

                #if defined(__IMXRT1062__) // Teensy 4.1
                    ws2812Serial[3] = new WS2812Serial(PPUC_NUM_LEDS_4, frameBuffer4, ws2812FXDevices[3][0]->getWS2812FX()->getPixels(), 17, PPUC_LED_TYPE_4);
                    ws2812Serial[3]->begin();
                    ws2812FXDevices[3][0]->getWS2812FX()->setCustomShow(EffectsController::ws2812SerialShow4);
                #endif

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
                ws2812FXDevices[4][0]->getWS2812FX()->init();
                ws2812FXDeviceCounters[4] = 1;

                #if defined(__IMXRT1062__) // Teensy 4.1
                    ws2812Serial[4] = new WS2812Serial(PPUC_NUM_LEDS_5, frameBuffer5, ws2812FXDevices[4][0]->getWS2812FX()->getPixels(), 20, PPUC_LED_TYPE_5);
                    ws2812Serial[4]->begin();
                    ws2812FXDevices[4][0]->getWS2812FX()->setCustomShow(EffectsController::ws2812SerialShow5);
                #endif

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
                ws2812FXDevices[5][0]->getWS2812FX()->init();
                ws2812FXDeviceCounters[5] = 1;

                #if defined(__IMXRT1062__) // Teensy 4.1
                    ws2812Serial[5] = new WS2812Serial(PPUC_NUM_LEDS_6, frameBuffer6, ws2812FXDevices[5][0]->getWS2812FX()->getPixels(), 24, PPUC_LED_TYPE_6);
                    ws2812Serial[5]->begin();
                    ws2812FXDevices[5][0]->getWS2812FX()->setCustomShow(EffectsController::ws2812SerialShow6);
                #endif

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
                ws2812FXDevices[6][0]->getWS2812FX()->init();
                ws2812FXDeviceCounters[6] = 1;

                #if defined(__IMXRT1062__) // Teensy 4.1
                    ws2812Serial[6] = new WS2812Serial(PPUC_NUM_LEDS_7, frameBuffer7, ws2812FXDevices[6][0]->getWS2812FX()->getPixels(), 29, PPUC_LED_TYPE_7);
                    ws2812Serial[6]->begin();
                    ws2812FXDevices[6][0]->getWS2812FX()->setCustomShow(EffectsController::ws2812SerialShow7);
                #endif

                ws2812FXDevices[6][0]->off();
                ws2812FXstates[6] = true;
            #endif
            _testButtons = new EffectControllerTestButtons(_eventDispatcher);

            if (platform == PLATFORM_WPC) {
                _generalIllumintationWPC = new GeneralIlluminationWPC(_eventDispatcher);
                _generalIllumintationWPC->start();
            }
        }
        else if (controllerType == CONTROLLER_NANO_PIN2DMD_GI) {
            _ledBuiltInDevice = new LedBuiltInDevice();
            _ledBuiltInDevice->on();
            _nullDevice = new NullDevice();
            _shakerPWMDevice = new WavePWMDevice(9);
            _shakerPWMDevice->off();
            #if defined(PIN_A0)
                brightnessControlBasePin = PIN_A0;
            #endif
            #if defined(PPUC_NUM_LEDS_1) && defined(PPUC_LED_TYPE_1)
                ws2812FXDevices[0][0] = new WS2812FXDevice(
                    new WS2812FX(PPUC_NUM_LEDS_1, 6, PPUC_LED_TYPE_1),
                    0,
                    PPUC_NUM_LEDS_1 - 1,
                    0,
                    0
                );
                ws2812FXDevices[0][0]->getWS2812FX()->init();
                ws2812FXDeviceCounters[0] = 1;

                ws2812FXDevices[0][0]->off();
                ws2812FXstates[0] = true;
            #endif
        }
        else if (controllerType == CONTROLLER_16_8_1) {
            // Read bordID.
            // @todo draft!
            boardId = (analogRead(28) - 100) / 16 ;
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

    void handleEvent(ConfigEvent* event);

    #if defined(__IMXRT1062__) // Teensy 4.1
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
    #endif

private:
    EventDispatcher* _eventDispatcher;
    LedBuiltInDevice* _ledBuiltInDevice;
    NullDevice* _nullDevice;
    WavePWMDevice* _shakerPWMDevice;
    WavePWMDevice* _ledPWMDevice;
    RgbStripDevice* _rgbStripeDevice;
    WS2812FXDevice* ws2812FXDevices[PPUC_MAX_WS2812FX_DEVICES][10];
    int ws2812FXDeviceCounters[PPUC_MAX_WS2812FX_DEVICES] = {0};
    bool ws2812FXstates[PPUC_MAX_WS2812FX_DEVICES] = {0};
    bool ws2812FXrunning[PPUC_MAX_WS2812FX_DEVICES] = {0};
    bool ws2812FXbrightness[PPUC_MAX_WS2812FX_DEVICES] = {0};
    #if defined(__IMXRT1062__) // Teensy 4.1
        WS2812Serial* ws2812Serial[PPUC_MAX_WS2812FX_DEVICES];
    #endif
    EffectContainer* stackEffectContainers[EFFECT_STACK_SIZE];
    int stackCounter = -1;
    byte brightnessControl[PPUC_MAX_WS2812FX_DEVICES] = {0};
    byte brightnessControlReads[PPUC_MAX_BRIGHTNESS_CONTROLS] = {0};
    byte brightnessControlBasePin = 0;

    int mode = 0;

    byte platform;
    byte controllerType;
    byte boardId = 255;
    byte config_port = 0;
    byte config_type = 0;
    byte config_amount = 0;
    byte config_afterGlow = 0;
    byte config_heatUp = 0;

    unsigned long ws2812UpdateInterval = 0;
    unsigned long ws2812AfterGlowUpdateInterval = 0;
    unsigned long brightnessUpdateInterval = 0;

    EffectControllerTestButtons* _testButtons;
    GeneralIlluminationWPC* _generalIllumintationWPC;

    static EffectsController* effectsControllerInstance;
};

#endif
