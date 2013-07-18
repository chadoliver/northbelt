#include "ch.h"
#include "hal.h"
#include "startThread.c"
#include "messages.c"

#define BLUE_LED GPIOD_LED6
#define ORANGE_LED GPIOD_LED3
#define YELLOW_LED GPIOD_LED4
#define LED_PERIOD 200
#define LED_DELAY LED_PERIOD/2


void console_init(void) {
    const SerialConfig sd2config = {9600, 0, 0, 0};
    sdStart(&SD2, &sd2config);
};

int console_readChar(int timeoutInMilliseconds) {
    // serial input can be Q_TIMEOUT, Q_RESET, or a char
    int character = Q_RESET;
    while (character == Q_RESET) {
        character = chnGetTimeout(&SD2, MS2ST(timeoutInMilliseconds));
    }
    return character;
};

MessageWrapper* console_readMessage(int timeoutInMilliseconds) {

    MessageWrapper* msg = messages_new();

    if (msg != NULL) {
        msg->tag = 1;

        int index = 0;
        int character = console_readChar(timeoutInMilliseconds); // we have to use type int because Q_TIMEOUT isn't a char
        if (character == Q_TIMEOUT) {
            // timeout on the first readChar() call means that there's nothing to read.
            messages_releaseMemory(msg);
            msg = NULL;
        }

        while ((character != Q_TIMEOUT) && (character != '\0') && (index < 99)) {
            msg->message[index] = character;
            character = console_readChar(timeoutInMilliseconds);
            index++;
        }
    }
    return msg;
}

void console_printChar(char character) {
    chnPutTimeout(&SD2, character, TIME_IMMEDIATE);
};

void console_printMessage(MessageWrapper* msg) {

    int i = 0;
    while (msg->message[i] != '\0') {
        console_printChar(msg->message[i]);
        i++;
    }
    console_printChar('\n');
};

static msg_t console(void *arg) {

    (void) arg;
    chRegSetThreadName("console");

    console_init();
    messages_init();

    while (TRUE) {
        MessageWrapper* msg = console_readMessage(0);
        if (msg != NULL) console_printMessage(msg);
        messages_releaseMemory(msg);
    }

    return 0;
}

