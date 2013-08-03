
#include <ch.hpp>
#include <hal.hpp>
#include "serialChannel.hpp"

#include <types.hpp>
#include <buffer.hpp>

#include <imuThread.hpp>
#include <orientationThread.hpp>
#include <outputThread.hpp>

// #include "bluetoothChannel.c"

int main(void) {

	halInit();
	chSysInit();
    
    /*
    Buffer<imu_state> imuToOrientation;
    Buffer<imu_state> orientationToOut;
    
    IMUThread<1024> imuThread;
    OrientationThread<1024> orientationThread;
    */  
    OutputThread<8192> outputThread;
    
    
    /*
    imuThread.downstreamBuffer = imuToOrientation;
    orientationThread.upstreamBuffer = imuToOrientation;
    orientationThread.downstreamBuffer = orientationToOutput;
    outputThread.upstreamBuffer = orientationToOutput;
    
    imuThread.start(NORMALPRIO+1);
    orientationThread.start(NORMALPRIO);
    */
    outputThread.start(NORMALPRIO);
    
	while (TRUE) chThdSleepMilliseconds(500);

	return 0;
};

