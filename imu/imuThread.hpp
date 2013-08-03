#ifndef IMU_H_
#define IMU_H_

#include <ch.hpp>
#include <types.h>

#define IMU_THREAD_SIZE 1024

template <uint32_t thread_memory_size>
class IMUThread : public BaseStaticThread<thread_memory_size> {
    
    private:
        I2CDriver* i2c_driver;
        HMC5883L hmc5883l;
        MPU6050 mpu6050;
        EXTConfig extcfg;
        Buffer<imu_state> downstreamBuffer;
        
    protected:
        virtual msg_t main(void) : BaseStaticThread<thread_memory_size>();
    
    public:
        void IMUThread(void);
};

#endif

