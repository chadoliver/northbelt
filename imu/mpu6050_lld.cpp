#include "hal.h"
#include "ch.h"
#include "mpu6050_lld.h"


void MPU6050::MPU6050 (I2CDriver* i2c_instance) {
    
    i2c_driver = i2c_instance;
    
    reg_data rdata;

    write_register(MPU6050_PWR_MGMT_1, MPU6050_PM1_RESET);
    chThdSleepMilliseconds(200);  // wait for device reset

    write_register(MPU6050_SIGNAL_PATH_RESET, 0b111);
    chThdSleepMilliseconds(200);  // wait for signal path reset

	rdata = MPU6050_PM1_X_GYRO_CLOCKREF & (~(MPU6050_PM1_SLEEP));   // make sure device is 'awake'
    write_register(MPU6050_PWR_MGMT_1, rdata);

	rdata = 16;                                          // 2 ms sample period.
    write_register(MPU6050_SMPLRT_DIV, rdata);

	rdata = MPU6050_I2C_BYPASS | MPU6050_INT_LEVEL | MPU6050_LATCH_INT_EN;
	write_register(MPU6050_INT_PIN_CFG, rdata);

    //rdata = MPU6050_I2C_MST_EN;
    //mpu6050_write_register(MPU6050_USER_CTRL, rdata);

	rdata = MPU6050_A_HPF_RESET | MPU6050_A_SCALE_pm8g;
	write_register(MPU6050_ACCEL_CONFIG, rdata);

	rdata = MPU6050_G_SCALE_pm500;
	write_register(MPU6050_GYRO_CONFIG, rdata);

	rdata = MPU6050_INT_EN_DATA_RD_EN;
    write_register(MPU6050_INT_ENABLE, rdata);

    serial_printString("Successfully configured MPU-9150.");

    write_register(MPU6050_USER_CTRL, 0b01000000);

    rdata = read_register(MPU6050_USER_CTRL);
    serial_printInt(rdata);
};

void MPU6050::write_register(mpu6050_regaddr address, reg_data rdata) {
    Sensor::write_register ((uint8_t) address, rdata)
};

reg_data MPU6050::read_register(mpu6050_regaddr address) {
    i2c_data rxbuf Sensor::read_register((uint8_t) address, 1);
    return rxbuf;
};

vector3 read_accel();
vector3 read_gyro();
        
vector3 MPU6050::read_measurement(mpu6050_regaddr address) {
    
    vector3 measurement;
    
    i2c_data received[6] = Sensor::read_register((uint8_t) address, 6);

    measurement.x = (received[0] << 8) | received[1];
    measurement.y = (received[2] << 8) | received[3];
    measurement.z = (received[4] << 8) | received[5];
    
    return measurement;
};

vector3 MPU6050::read_accel(void) {
    return read_measurement(MPU6050_ACCEL_XOUT_H);
};

vector3 MPU6050::read_rot(void) {
    return read_measurement(MPU6050_GYRO_XOUT_H);
};
















