// heading.c

#include "hal.h"
#include "ch.h"
#include "imu.h"
#include "compass.h"
#include "serialChannel.h"

/* Important Link: http://www.x-io.co.uk/open-source-imu-and-ahrs-algorithms/
 * That algorithm could be used to get an acceleration- and rotation-invariant heading.
 */

static msg_t heading(void *arg) {

    (void) arg;
    chRegSetThreadName("heading");
    
    imu_init();

    while (TRUE) {
        chThdSleepMilliseconds(500);

        vector3 accel = read_acceleration();
        vector3 rot   = read_rotation();
        vector3 mag   = read_magnetic_field();
        
        chprintf((BaseSequentialStream *)&SERIAL_DRIVER, "%d,%d,%d\n\r", accel.x, accel.y, accel.z);
        chprintf((BaseSequentialStream *)&SERIAL_DRIVER, "%d,%d,%d\n\r", rot.x, rot.y, rot.z);
        //chprintf((BaseSequentialStream *)&SERIAL_DRIVER, "%d,%d,%d\n\r", mag.x, mag.y, mag.z);
    }

    return 0;
}
