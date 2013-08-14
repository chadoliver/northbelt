#ifndef STARTTHREAD_C
#define STARTTHREAD_C

#include "ch.h"
#include "hal.h"

typedef msg_t (*threadF) (void *arg);

void startThread( threadF threadFunction, int workingAreaSize) {

    Thread* tp = chThdCreateFromHeap(
        NULL,
        THD_WA_SIZE(workingAreaSize),
        NORMALPRIO,
        threadFunction,
        NULL
    );
    if (tp == NULL) chSysHalt();    /* Memory exausted. */

    //return tp;
    // To reclaim the thread's space, call msg_t msg = chThdWait(tp)
};

#endif
