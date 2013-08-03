#include "hal.h"
#include "ch.h"
#include "serialChannel.hpp"

void SerialChannel :: SerialChannel(SerialDriver driver) {
    config = {9600, 0, 0, 0};
    sdStart(&driver, &config);
};

int SerialChannel :: readChar(int timeoutInMilliseconds) {
    // the result of chnGetTimeout can be Q_TIMEOUT, Q_RESET, or a char
    int character = Q_RESET;
    while (character == Q_RESET) {
        character = chnGetTimeout(&SERIAL_DRIVER, MS2ST(timeoutInMilliseconds));
    }
    return character;
};

void SerialChannel :: printChar(char character) {
    chnPutTimeout(&SERIAL_DRIVER, character, TIME_IMMEDIATE);
};

void SerialChannel :: printString(const char* string) {
    chprintf((BaseSequentialStream *)&SERIAL_DRIVER, "%s\n\r", string);
    //chprintf((BaseSequentialStream *)&SD2, "@stdout@%s\n", string);
};

void SerialChannel :: printInt(int integer) {
    chprintf((BaseSequentialStream *)&SERIAL_DRIVER, "%u\n\r", integer);
};
