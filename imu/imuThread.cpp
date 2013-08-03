#include "hal.h"
#include "ch.h"
#include "types.h"
#include "mpu6050_lld.h"
#include "hmc5883l_lld.hpp"
#include "imu.hpp"

const I2CConfig i2c_config = {
    OPMODE_I2C,
    400000,                // i2c clock speed, as specified in mpu6050 datasheet.
    FAST_DUTY_CYCLE_2,
};

void IMUThread::IMUThread(void) : BaseStaticThread<thread_memory_size>() {
    // pass
};

virtual msg_t IMUThread::main(void) {
    
    setName("imu-thread");
    
    imu_state* state;
    i2c_driver = I2CD3;
    i2cStart(&i2c_driver, &i2c_config);
    
    hmc5883l = HMC5883L(&i2c_driver);
    mpu6050 = MPU6050(&i2c_driver);
    
    // The STM32F4 multiplexes all ports together. An interrupt handler can be assigned to
    // a specific pin but not a specific port (e.g. if you want to monitor PA1, it
    // will also be triggered by PB1 and PC1 etc).
    // Data ready on the HMC5883L is indicated by PC14 going low for 250usec, and data ready 
    // on the MPU6050 is indicated by PB5 going to the level configured in Register 55.
    EXTConfig extcfg = {
        {
            {EXT_CH_MODE_DISABLED, NULL},   // 0
            {EXT_CH_MODE_DISABLED, NULL},   // 1
            {EXT_CH_MODE_DISABLED, NULL},   // 2
            {EXT_CH_MODE_DISABLED, NULL},   // 3
            {EXT_CH_MODE_DISABLED, NULL},   // 4
            {EXT_CH_MODE_FALLING_EDGE | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOB, mpu6050.signal_data_ready()},   // 5
            {EXT_CH_MODE_DISABLED, NULL},   // 6
            {EXT_CH_MODE_DISABLED, NULL},   // 7
            {EXT_CH_MODE_DISABLED, NULL},   // 8
            {EXT_CH_MODE_DISABLED, NULL},   // 9
            {EXT_CH_MODE_DISABLED, NULL},   // 10
            {EXT_CH_MODE_DISABLED, NULL},   // 12
            {EXT_CH_MODE_DISABLED, NULL},   // 13
            {EXT_CH_MODE_FALLING_EDGE | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOC, hmc5883l.signal_data_ready()},   // 14
            {EXT_CH_MODE_DISABLED, NULL},   // 15
        }
    };
    
    extStart(&EXTD1, &extcfg);
    
    state = downstreamBuffer.switch_upstream();    // this returns a pointer to the new 'upstream' imu_state object.

    while (1) {
        
        // Wait for the hmc5883l, then read the new data. This has the lowest sampling rate,  
        // so reading from this first will allow us to minimise the inter-sample time.
        hmc5883l.wait_for_data();
        state.mag = hmc5883l.read_mag();
        
        // Wait for the mpu6050, then read the new data.
        mpu6050.wait_for_data();
        state.rot = mpu6050.read_rot(),
        state.accel = mpu6050.read_accel(),
        
        // Send the data to the heading thread.
        state = downstreamBuffer.switch_upstream();
    }

    return 0;
};