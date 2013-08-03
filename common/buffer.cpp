#include "hal.h"
#include "ch.h"
#include "types.h"
#include "imu.h"
#include "startThread.c"

Buffer::Buffer(void) {
    
    // Key idea: there are three items of type BufferedType, At any time, one of these is
    // acting as the 'waiting' object, one is being populated by the producer (upstream 
    // thread), and one is being examined by the consumer (downstream thread). Items
    // do not have a fixed role; their role is recorded and changed by using three
    // pointers (upstrea, waiting, downstream).
    
    upstream_ptr = &payloads[0];
    waiting_ptr = &payloads[1];
    downstream_ptr = &payloads[2];
};

BufferedType* Buffer::switch_upstream(void) {
    // This function swaps the 'waiting' and 'upstream' pointers, and returns a copy
    // of the new upstream pointer. If the upstream thread retains a copy of the old 
    // 'upstream' pointer (which now points to the 'waiting' item), Bad Things can
    // happen. Thus, the reference to the old pointer should be overwritten by the
    // new pointer. Here's an example:
    // 
    //      *state_ptr = make_some_data();
    //      ptr_to_fresh_state_object = buffer.switch_upstream();
    //      state_ptr = ptr_to_fresh_state_object;
    
    chSysLock();    // Disable interrupts. The following actions should be atomic.
        BufferedType* temp = upstream_ptr;
        upstream_ptr = waiting_ptr;
        waiting_ptr = temp;
    chSysUnlock();
    
    return upstream;
};

BufferedType* Buffer::switch_downstream(void) {
    // See the comments for switch_upstream().
    
    chSysLock();    // Disable interrupts. The following actions should be atomic.
        BufferedType* temp = downstream_ptr;
        downstream_ptr = waiting_ptr;
        waiting_ptr = temp;
    chSysUnlock();
    
    return downstream;
};