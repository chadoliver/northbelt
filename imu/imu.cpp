#include "hal.h"
#include "ch.h"
#include "types.h"
#include "mpu6050_lld.h"
#include "hmc5883l_lld.h"
#include "imu.h"
#include "startThread.c"

const I2CConfig i2c_config = {
    OPMODE_I2C,
    400000,                // i2c clock speed, as specified in mpu6050 datasheet.
    FAST_DUTY_CYCLE_2,
};

class IMU {
    
    private:
        I2CDriver* i2c_driver;
        HMC5883L hmc5883l;
        MPU6050 mpu6050;
    
    public:
        Buffer<imu_state> buffer;
        void IMU(void);
        imu_state read_state(void);
        static msg_t processor(void *arg)
};

void IMU::IMU(Buffer<imu_state> output_buffer) {
    
    buffer = output_buffer;
    
    i2c_driver = I2CD3;
    i2cStart(&i2c_driver, &i2c_config);
    
    hmc5883l = HMC5883L(&i2c_driver);
    mpu6050 = MPU6050(&i2c_driver);
    
    // need to set up the semaphores. Actually, these will probably be defined in the sensor child classes.
};

imu_state IMU::read_state(void) {
    
    imu_state state = {
        mpu6050.read_rot(),
        mpu6050.read_accel(),
        hmc5883l.read_mag(),
    };

    return state;
}

static msg_t IMU::processor(void *arg) {

    (void) arg;
    chRegSetThreadName("imu-processor");

    while (1) {
        imu_state state;
        
        // Wait for the hmc5883l, then read the new data. This has the lowest sampling rate,  
        // so reading from this first will allow us to minimise the inter-sample time.
        hmc5883l.wait_for_data();
        state.mag = hmc5883l.read_mag();
        
        // Wait for the mpu6050, then read the new data.
        mpu6050.wait_for_data();
        state.rot = mpu6050.read_rot(),
        state.accel = mpu6050.read_accel(),
        
        // Push the data into the buffer.
        buffer.push(state);
    }

    return 0;
};






















