#ifndef BUFFER_H_
#define BUFFER_H_

#include <ch.hpp>
#include <hal.h>

template <class BufferedType>
class Buffer {

    private:
        BufferedType payloads [3];
        BufferedType* upstream_ptr;     // This is a pointer to the object which is being used (populated) by the producer.
        BufferedType* waiting_ptr;      // A pointer to the buffered object.
        BufferedType* downstream_ptr;     // A pointer to the object which is being used (examined) by the consumer.
        
    public:
        Buffer (void);
        BufferedType* switch_upstream (void);
        BufferedType* switch_downstream (void);
};


template <class BufferedType>
Buffer<BufferedType>::Buffer (void) {    
    upstream_ptr = &payloads[0];
    waiting_ptr = &payloads[1];
    downstream_ptr = &payloads[2];
};

template <class BufferedType>
BufferedType* Buffer<BufferedType>::switch_upstream () {
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
    
    return upstream_ptr;
};

template <class BufferedType>
BufferedType* Buffer<BufferedType>::switch_downstream() {
    // See the comments for switch_upstream().
    
    chSysLock();    // Disable interrupts. The following actions should be atomic.
        BufferedType* temp = downstream_ptr;
        downstream_ptr = waiting_ptr;
        waiting_ptr = temp;
    chSysUnlock();
    
    return downstream_ptr;
};


#endif
