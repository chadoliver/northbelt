#ifndef OUTPUT_THREAD_H_
#define OUTPUT_THREAD_H_

#include <ch.hpp>
#include <types.h>
#include <buffer.hpp>
#include <pin.hpp>
#include <pinArray.hpp>

template <uint32_t thread_memory_size>
class OutputThread : public BaseStaticThread<thread_memory_size> {
    
    private:
        Buffer<imu_state> upstreamBuffer;
        Buffer<imu_state> downstreamBuffer;
        PinArray<16> pinArray;
        
    protected:
        virtual msg_t main(void) : BaseStaticThread<thread_memory_size>();
    
    public:
        void OutputThread(void);
};

#endif

