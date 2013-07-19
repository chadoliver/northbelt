#ifndef IMU_H_
#define IMU_H_

#include "types.h"

typedef struct imu_state {
	vector3 rot;
	vector3 accel;
    vector3 mag;
} imu_state;


void imu_init(void);

imu_state imu_read_state(void);
