#ifndef MPU6050_LLD_H_
#define MPU6050_LLD_H_

#include <hal.h>
#include <ch.hpp>
#include <types.hpp>
#include <sensors.hpp>
#include <mpu6050_register_map.hpp>

class MPU6050: public Sensor {
    
    private:
        static const uint8_t device_address = 0x68;
        
        void configure_device(void);
        uint8_t getDeviceAddress(void);
    
    public:
        
        void write_register (mpu6050_regaddr address, reg_data rdata);
        reg_data* read_register (mpu6050_regaddr address, int rx_bytes);
        vector3 read_accel (void);
        vector3 read_rot (void);
};

#endif
