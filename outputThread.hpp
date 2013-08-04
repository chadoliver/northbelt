#ifndef OUTPUT_THREAD_H_
#define OUTPUT_THREAD_H_

#include <ch.hpp>
#include <types.hpp>
#include <buffer.hpp>
#include <pin.hpp>
#include <pinArray.hpp>

class OutputThread: public chibios_rt::BaseStaticThread<8192> {
    
    private:
        PinArray pinArray;
                
    protected:        
        msg_t main(void);

    public:
        Buffer<imu_state> upstreamBuffer;
        Buffer<imu_state> downstreamBuffer;
};

msg_t OutputThread::main(void) {
    
    this->setName("output-thread");
    
    pinArray.pins[0].init( GPIOA,  9);
    pinArray.pins[1].init( GPIOA,  8);
    pinArray.pins[2].init( GPIOC,  9);
    pinArray.pins[3].init( GPIOC,  8);
    pinArray.pins[4].init( GPIOC,  7);
    pinArray.pins[5].init( GPIOC,  6);
    pinArray.pins[6].init( GPIOB, 15);
    pinArray.pins[7].init( GPIOB, 14);
    pinArray.pins[8].init( GPIOB,  4);
    pinArray.pins[9].init( GPIOA, 10);
    pinArray.pins[10].init( GPIOD,  2);
    pinArray.pins[11].init( GPIOC, 12);
    pinArray.pins[12].init( GPIOC, 11);
    pinArray.pins[13].init( GPIOC, 10);
    pinArray.pins[14].init( GPIOA, 12);
    pinArray.pins[15].init( GPIOA, 11);
    
    pinArray.setGroupLevel(0);
    pinArray.setGroupMode(PAL_MODE_OUTPUT_PUSHPULL);
    
    
    uint16_t updatePeriod = 100;
    
    
    while (1) {
        uint8_t i;
        for (i=0; i<pinArray.length; i++) {
            pinArray.choose(i);
            chThdSleepMilliseconds(updatePeriod/2);
        }
    }

    return 0;
};

#endif

