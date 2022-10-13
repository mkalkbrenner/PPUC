// Markus Kalkbrenner 2022
// Note to self: Play more pinball!

#include <EffectDevices/Definitions.h>

#define PPUC_NUM_LEDS_1 60
#define PPUC_LED_TYPE_1 SK6812_GBRW
#define PPUC_NUM_LEDS_2 1
#define PPUC_LED_TYPE_2 WS2812_GRB
#define PPUC_NUM_LEDS_3 1000
#define PPUC_LED_TYPE_3 WS2812_GRB
#define PPUC_NUM_LEDS_4 23
#define PPUC_LED_TYPE_4 WS2812_GRB
#define PPUC_NUM_LEDS_5 18
#define PPUC_LED_TYPE_5 WS2812_GRB
#define PPUC_NUM_LEDS_6 60
#define PPUC_LED_TYPE_6 WS2812_GRB
#define PPUC_NUM_LEDS_7 60
#define PPUC_LED_TYPE_7 WS2812_GRB

#include <EffectsController.h>

EffectsController effectsController("0.1.0", PLATFORM_SYS11);

void setup() {
    // Debug
    Serial.begin(9600); // USB is always 12 Mbit/sec

    effectsController.eventDispatcher()->addListener(new CrossLinkDebugger());

    // Setup
    effectsController.eventDispatcher()->setCrossLinkSerial(Serial8);

    effectsController.createCombinedGiAndLightMatrixWs2812FXDevice(7);

    effectsController.setBrightness(1, 64);
    effectsController.setBrightness(7, 128);
    //effectsController.attachBrightnessControl(7, 1);

    effectsController.giAndLightMatrix(7)->setHeatUp(40);
    effectsController.giAndLightMatrix(7)->setAfterGlow(280);

    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(1, 1, ORANGE); // HOLD
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(2, 2, ORANGE); // BONUS
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(3, 3, ORANGE); // DOUBLE
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(4, 4, ORANGE); // SCORES
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(5, 5, ORANGE); // CYCLONE 50K
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(6, 6, ORANGE); // CYCLONE 100K
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(7, 7, ORANGE); // CYCLONE Gate Bonis
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(8, 8, ORANGE); // RIDE THE COMET (on ramp)
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(9, 9, RED); // W/L SCORE FERRIS WHEEL BONUS
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(10, 10, ORANGE); // ADV. "X"
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(11, 11, ORANGE); // Balloon 25K (Ducks)
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(12, 12, ORANGE); // Balloon 50K (Ducks)
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(13, 13, ORANGE); // Balloon LITES EX. BALL (Ducks)
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(14, 14, ORANGE); // 1 (Gate Lane)
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(15, 15, ORANGE); // 2 (Gate Lane)
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(16, 16, RED); // 3 (Gate Lane)
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(17, 17, RED); // RIDE AGAIN
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(18, 18, RED); // SPINS MYSTERY WHEEL
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(19, 19, WHITE); // Ducks (top)
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(20, 20, WHITE); // Ducks (mid)
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(21, 21, WHITE); // Ducks (bottom)
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(22, 22, RED); // Ball Toss (top)
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(23, 23, YELLOW); // Ball Toss (mid)
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(24, 24, WHITE); // Ball Toss (bottom)
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(25, 25, YELLOW); // EXTRA BALL Left Outlane
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(26, 26, YELLOW); // EXTRA BALL Right Outlane
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(27, 27, YELLOW); // COMET 20K
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(28, 28, YELLOW); // COMET 40K
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(29, 29, YELLOW); // COMET 60K
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(30, 30, RED); // COMET 80K
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(31, 31, RED); // COMET 100K
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(32, 32, WHITE); // COMET 1 Million

    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(49, 33, YELLOW); // 2X
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(50, 34, YELLOW); // 7X
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(51, 35, YELLOW); // 6X
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(52, 36, WHITE); // 5X
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(53, 37, YELLOW); // 4X
    effectsController.giAndLightMatrix(7)->assignLedToLightMatrixSYS11(54, 38, YELLOW); // 3X

    // Test Buttons
    effectsController.addEffect(
            new LedBlinkEffect(),
            effectsController.ledBuiltInDevice(),
            new Event(EVENT_SOURCE_SWITCH, 201),
            1, // priority
            5, // repeat
            0  // mode
    );

    effectsController.addEffect(
            new NullEffect(),
            effectsController.ledBuiltInDevice(),
            new Event(EVENT_SOURCE_SWITCH, 202),
            2, // priority
            0, // repeat
            0  // mode
    );

    effectsController.addEffect(
            new LedBlinkEffect(),
            effectsController.ledBuiltInDevice(),
            new Event(EVENT_SOURCE_SWITCH, 203),
            1, // priority
            5, // repeat
            0  // mode
    );

    // Controller start
    effectsController.addEffect(
            new NullEffect(),
            effectsController.ledBuiltInDevice(),
            new Event(EVENT_SOURCE_SWITCH, 204),
            2, // priority
            0, // repeat
            0  // mode
    );

    // Start
    effectsController.start();
    //effectsController.generalIllumintationWPC()->start();
}

void loop() {
    effectsController.update();
}
