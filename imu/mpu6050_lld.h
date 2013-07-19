#ifndef MPU6050_LLD_H_
#define MPU6050_LLD_H_

#include "types.h"
#include "sensors.h"
#include "mpu6050_register_map.h"

class MPU6050: public Sensor {
    
    private:
        static const uint8_t device_address = 0x68;
    
    public:
        void MPU6050 (I2CDriver* i2c_instance);
        void write_register (mpu6050_regaddr address, reg_data rdata);
        reg_data read_register(mpu6050_regaddr address);
        vector3 read_measurement(mpu6050_regaddr address);
        vector3 read_accel(void);
        vector3 read_rot(void);
};

#endif