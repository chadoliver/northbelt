#include <hal.h>
#include <orientationThread.hpp>

/* Important Link: http://www.x-io.co.uk/open-source-imu-and-ahrs-algorithms/
 * That algorithm could be used to get an acceleration- and rotation-invariant heading.
 */
 
void OrientationThread::OrientationThread(void) : BaseStaticThread<thread_memory_size>() {
    // pass  
};

msg_t OrientationThread::main(void) {

    setName("orientation-thread");

    while (TRUE) {
        chThdSleepMilliseconds(500);
        
        imu_state* state = upstreamBuffer.switch_downstream();
        
        state->rot;
        state->accel;
        state->mag;
        
        
        
        
    }

    return 0;
}
