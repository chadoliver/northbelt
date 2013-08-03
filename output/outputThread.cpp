#include <outputThread.hpp>

void OutputThread::OutputThread(void) : BaseStaticThread<thread_memory_size>() {
    // pass  
};

virtual msg_t OutputThread::main(void) {
    
    setName("output-thread");
    
    pinArray.pins = {
        Pin (port, pin),
        Pin (port, pin),
        Pin (port, pin),
        Pin (port, pin),
        Pin (port, pin),
        Pin (port, pin),
        Pin (port, pin),
        Pin (port, pin),
        Pin (port, pin),
        Pin (port, pin),
        Pin (port, pin),
        Pin (port, pin),
        Pin (port, pin),
        Pin (port, pin),
        Pin (port, pin),
        Pin (port, pin),
    };
    
    pinArray.setGroupLevel(LOW);
    pinArray.setGroupMode(OUTPUT_PUSHPULL);
    
    uint16_t updatePeriod = 100;
    
    
    while (1) {
        uint8_t i;
        for (i=0; i<pinsArray.length; i++) {
            pinArray.set(i);
            chThdSleepMilliseconds(updatePeriod/2);
        }
    }

    return 0;
};