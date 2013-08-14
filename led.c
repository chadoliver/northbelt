#include "ch.h"
#include "hal.h"

#define ORANGE_LED GPIOD_LED3
#define YELLOW_LED GPIOD_LED4
#define RED_LED GPIOD_LED5
#define BLUE_LED GPIOD_LED6

#define FOREVER 0

void all_leds_init(void) {

    
    palSetPadMode(GPIOD, ORANGE_LED, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOD, YELLOW_LED, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOD, RED_LED, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOD, BLUE_LED, PAL_MODE_OUTPUT_PUSHPULL);

    /*
    palSetPadMode(GPIOE, GPIOE_PIN7, PAL_MODE_OUTPUT_PUSHPULL);     // led 1
    palSetPadMode(GPIOE, GPIOE_PIN9, PAL_MODE_OUTPUT_PUSHPULL);     // led 2
    palSetPadMode(GPIOE, GPIOE_PIN11, PAL_MODE_OUTPUT_PUSHPULL);    // led 3
    palSetPadMode(GPIOE, GPIOE_PIN13, PAL_MODE_OUTPUT_PUSHPULL);    // led 4
    palSetPadMode(GPIOE, GPIOE_PIN15, PAL_MODE_OUTPUT_PUSHPULL);    // led 5
    palSetPadMode(GPIOB, GPIOB_PIN11, PAL_MODE_OUTPUT_PUSHPULL);    // led 6
    palSetPadMode(GPIOB, GPIOB_PIN13, PAL_MODE_OUTPUT_PUSHPULL);    // led 7
    palSetPadMode(GPIOB, GPIOB_PIN15, PAL_MODE_OUTPUT_PUSHPULL);    // led 8
    palSetPadMode(GPIOE, GPIOE_PIN12, PAL_MODE_OUTPUT_PUSHPULL);    // led 9
    palSetPadMode(GPIOE, GPIOE_PIN10, PAL_MODE_OUTPUT_PUSHPULL);    // led 10
    palSetPadMode(GPIOE, GPIOE_PIN8, PAL_MODE_OUTPUT_PUSHPULL);     // led 11
    palSetPadMode(GPIOB, GPIOB_PIN2, PAL_MODE_OUTPUT_PUSHPULL);     // led 12
    palSetPadMode(GPIOB, GPIOB_PIN0, PAL_MODE_OUTPUT_PUSHPULL);     // led 13
    palSetPadMode(GPIOC, GPIOC_PIN4, PAL_MODE_OUTPUT_PUSHPULL);     // led 14
    palSetPadMode(GPIOB, GPIOB_PIN1, PAL_MODE_OUTPUT_PUSHPULL);     // led 15
    palSetPadMode(GPIOC, GPIOC_PIN5, PAL_MODE_OUTPUT_PUSHPULL);     // led 16
    */
}

void all_leds_off(void) {

    palClearPad(GPIOD, ORANGE_LED);
    palClearPad(GPIOD, YELLOW_LED);
    palClearPad(GPIOD, RED_LED);
    palClearPad(GPIOD, BLUE_LED);

    palClearPad(GPIOE, GPIOE_PIN7);     // led 1
    palClearPad(GPIOE, GPIOE_PIN9);     // led 2
    palClearPad(GPIOE, GPIOE_PIN11);    // led 3
    palClearPad(GPIOE, GPIOE_PIN13);    // led 4
    palClearPad(GPIOE, GPIOE_PIN15);    // led 5
    palClearPad(GPIOB, GPIOB_PIN11);    // led 6
    palClearPad(GPIOB, GPIOB_PIN13);    // led 7
    palClearPad(GPIOB, GPIOB_PIN15);    // led 8
    palClearPad(GPIOE, GPIOE_PIN12);    // led 9
    palClearPad(GPIOE, GPIOE_PIN10);    // led 10
    palClearPad(GPIOE, GPIOE_PIN8);     // led 11
    palClearPad(GPIOB, GPIOB_PIN2);     // led 12
    palClearPad(GPIOB, GPIOB_PIN0);     // led 13
    palClearPad(GPIOC, GPIOC_PIN4);     // led 14
    palClearPad(GPIOB, GPIOB_PIN1);     // led 15
    palClearPad(GPIOC, GPIOC_PIN5);     // led 16
}

void led_init(void) {
    all_leds_init();
    all_leds_off();
};

void select_led(int led) {

    all_leds_off();

    switch (led) {

        case 0:
            palSetPad(GPIOE, GPIOE_PIN7);
            break;

        case 1:
            palSetPad(GPIOE, GPIOE_PIN9);
            break;

        case 2:
            palSetPad(GPIOE, GPIOE_PIN11);
            break;

        case 3:
            palSetPad(GPIOE, GPIOE_PIN13);
            break;

        case 4:
            palSetPad(GPIOE, GPIOE_PIN15);
            break;

        case 5:
            palSetPad(GPIOB, GPIOB_PIN11);
            break;

        case 6:
            palSetPad(GPIOB, GPIOB_PIN13);
            break;

        case 7:
            palSetPad(GPIOB, GPIOB_PIN15);
            break;

        case 8:
            palSetPad(GPIOE, GPIOE_PIN12);
            break;

        case 9:
            palSetPad(GPIOE, GPIOE_PIN10);
            break;

        case 10:
            palSetPad(GPIOE, GPIOE_PIN8);
            break;

        case 11:
            palSetPad(GPIOB, GPIOB_PIN2);
            break;

        case 12:
            palSetPad(GPIOB, GPIOB_PIN0);
            break;

        case 13:
            palSetPad(GPIOC, GPIOC_PIN4);
            break;

        case 14:
            palSetPad(GPIOB, GPIOB_PIN1);
            break;

        case 15:
            palSetPad(GPIOC, GPIOC_PIN5);
            break;
    }
};


