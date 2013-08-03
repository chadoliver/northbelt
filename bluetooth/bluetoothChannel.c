#ifndef BLUETOOTHCHANNEL_C
#define BLUETOOTHCHANNEL_C

#include <chprintf.h>

#define BLUETOOTH_DRIVER UARTD2

void bluetooth_init(void) {
    //const SerialConfig config = {9600, 0, 0, 0};

    palSetPadMode(GPIOD, 8, PAL_MODE_ALTERNATE(7));
    palSetPadMode(GPIOD, 9, PAL_MODE_ALTERNATE(7));
    
    uartStart(&BLUETOOTH_DRIVER, NULL);
};

void bluetooth_printString(const char* message, int length) {
    //chprintf((BaseSequentialStream *)&BLUETOOTH_DRIVER, "%s\r\n", string);

    uartStopReceive(&UARTD2);
    uartStopSend(&UARTD2);
    uartStartSend(&UARTD2, length, message);
    uartStopSend(&UARTD2);
};

#endif
