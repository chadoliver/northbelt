#ifndef IMU_H_
#define IMU_H_

#include <ch.hpp>
#include <types.hpp>
#include <mpu6050_lld.hpp>
#include <hmc5883l_lld.hpp>
#include <buffer.hpp>

class IMUThread : public chibios_rt::BaseStaticThread<1024> {
    
    private:
        I2CDriver i2c_driver;
        HMC5883L hmc5883l;
        MPU6050 mpu6050;
        EXTConfig extcfg;
        
    protected:        
        msg_t main(void);

    public:
        Buffer<imu_state> downstreamBuffer;
};




#endif

