#include <outputThread.hpp>

OutputThread::OutputThread(void) : BaseStaticThread<8192>() {
    // pass  
};

virtual msg_t OutputThread::main(void) {
    
    setName("output-thread");
    
    pinArray.pins = {
        Pin (GPIOA, 9),
        Pin (GPIOA, 8),
        Pin (GPIOC, 9),
        Pin (GPIOC, 8),
        Pin (GPIOC, 7),
        Pin (GPIOC, 6),
        Pin (GPIOB, 15),
        Pin (GPIOB, 14),
        Pin (GPIOB, 4),
        Pin (GPIOA, 10),
        Pin (GPIOD, 2),
        Pin (GPIOC, 12),
        Pin (GPIOC, 11),
        Pin (GPIOC, 10),
        Pin (GPIOA, 12),
        Pin (GPIOA, 11),
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
