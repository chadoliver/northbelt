
#include "ch.h"
#include "hal.h"
#include "startThread.c"
#include "serialChannel.h"
#include "watchdog.c"
#include "heading.c"

//#include "bluetoothChannel.c"

int main(void) {

	halInit();
	chSysInit();
    serial_init();
    
    startThread(watchdog, 512);
    
    //bluetooth_init();
    startThread(heading, 8192);
    
	while (TRUE) {
        chThdSleepMilliseconds(500);
    }

	return 0;
};

