#include "startThread.c"
#include "led.c"

#define TICKER_PERIOD 250

static msg_t watchdog(void *arg) {

    (void) arg;
    chRegSetThreadName("watchdog");

    //serial_printString("starting");

    led_init();

    int led = 0;
    int led_period = TICKER_PERIOD/16;

    palSetPad(GPIOD, GPIOD_LED6);
    chThdSleepMilliseconds(TICKER_PERIOD);

    while (TRUE) {

        for (led=0; led<16; led++) {
            select_led(led);
            chThdSleepMilliseconds(led_period);
        }
    }

    return 0;
};
