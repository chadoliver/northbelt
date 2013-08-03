#ifndef OUTPUT_THREAD_H_
#define OUTPUT_THREAD_H_

#include <ch.hpp>
#include <types.hpp>
#include <buffer.hpp>
#include <pin.hpp>
#include <pinArray.hpp>

class OutputThread : public BaseStaticThread<8192> {
    
    private:
        Buffer<imu_state> upstreamBuffer;
        Buffer<imu_state> downstreamBuffer;
        PinArray<16> pinArray;
        
    protected:
        virtual msg_t main(void);
    
    public:
        OutputThread(void) : BaseStaticThread<8192>();
};

#endif

