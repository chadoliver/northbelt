#include "ch.h"
#include "hal.h"

#define MESSAGE_STRING_LEN 100
#define POOL_SIZE 100

MemoryPool pool;

typedef struct {
    int tag;
    char message[MESSAGE_STRING_LEN];
} MessageWrapper;

void messages_init(void) {

    // align data, this depends on your compiler. this works for GCC
    MessageWrapper data[POOL_SIZE] __attribute__((aligned(sizeof(stkalign_t))));

    chPoolInit(&pool, sizeof(MessageWrapper), NULL);

    int i;
    for (i=0; i < POOL_SIZE; i++) {
        // add each element to the pool; i.e. make sure each element is marked as 'free'
        chPoolFree(&pool, &data[i]);
    }
};

MessageWrapper* messages_new(void) {
    return (MessageWrapper*) chPoolAlloc(&pool);
};

void messages_releaseMemory(MessageWrapper* msg) {
    chPoolFree(&pool, msg);
};
