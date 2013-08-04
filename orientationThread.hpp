#ifndef ORIENTATION_THREAD_H_
#define ORIENTATION_THREAD_H_

#include <ch.hpp>
#include <types.h>
#include <buffer.hpp>

template <uint32_t thread_memory_size>
class OrientationThread : public BaseStaticThread<thread_memory_size> {
    
    private:
        Buffer<imu_state> upstreamBuffer;
        Buffer<imu_state> downstreamBuffer;
        
    protected:
        virtual msg_t main(void) : BaseStaticThread<thread_memory_size>();
    
    public:
        void OrientationThread(void);
};

#endif

