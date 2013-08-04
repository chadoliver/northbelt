#include <ch.hpp>
#include <hal.h>

//#include <serialChannel.hpp>
//#include <bluetoothChannel.c>

#include <types.hpp>
#include <buffer.hpp>

#include <imuThread.hpp>
//#include <orientationThread.hpp>
#include <outputThread.hpp>

int main(void) {

	halInit();
	chSysInit();
    
    Buffer<imu_state> imuToOrientation;
    Buffer<imu_state> orientationToOutput;
    
    IMUThread imuThread;
    //OrientationThread<1024> orientationThread;
    OutputThread outputThread;
    
    imuThread.downstreamBuffer = imuToOrientation;
    //orientationThread.upstreamBuffer = imuToOrientation;
    //orientationThread.downstreamBuffer = orientationToOutput;
    outputThread.upstreamBuffer = orientationToOutput;
    
    imuThread.start(NORMALPRIO+1);
    //orientationThread.start(NORMALPRIO);
    outputThread.start(NORMALPRIO);
    
	while (TRUE) chThdSleepMilliseconds(500);

	return 0;
};
