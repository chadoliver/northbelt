#ifndef BUFFER_H_
#define BUFFER_H_

template <class BufferedType>
class Buffer {
    
    private:
        BufferedType payloads [3];
        BufferedType* upstream_ptr;     // This is a pointer to the object which is being used (populated) by the producer.
        BufferedType* waiting_ptr;      // A pointer to the buffered object.
        BufferedType* downstream_ptr;     // A pointer to the object which is being used (examined) by the consumer.  
    
    public:
        void Buffer(void);
        BufferedType* switch_upstream(void);
        BufferedType* switch_downstream(void);
};

#endif