#include "hal.h"
#include "ch.h"
#include "sensor.h"
#include "serialChannel.h"
#include "imu.h"
#include "mpu6050_register_map.h"

const uint8_t mpu6050_addr = 0x68;    // See page 8 , MPU6050 Register Map and Descriptions r4.0

i2c_Transaction mpu6050_transaction;

static void printAnyErrors(msg_t status) {
	if (status != RDY_OK){
        serial_printString("status:");
        serial_printInt(status);
        serial_printString("i2c_errors:");
        serial_printInt(i2cGetErrors(&I2C_DRIVER));
        serial_printString("");
	}
}

static void mpu6050_write_register(mpu6050_regaddr address, reg_data rdata) {
	msg_t status = RDY_OK;

	mpu6050_transaction.txbuf[0] = address;
	mpu6050_transaction.txbuf[1] = rdata;
	i2cAcquireBus(&I2C_DRIVER);
	status = i2cMasterTransmitTimeout(&I2C_DRIVER, mpu6050_addr, mpu6050_transaction.txbuf, 2, mpu6050_transaction.rxbuf, 0, sensor_i2c_timeout);
	i2cReleaseBus(&I2C_DRIVER);

	printAnyErrors(status);
}

reg_data mpu6050_read_register(mpu6050_regaddr address) {

    msg_t status = RDY_OK;
    reg_data rdata = 0;

	mpu6050_transaction.txbuf[0] = address;
	i2cAcquireBus(&I2C_DRIVER);
	status = i2cMasterTransmitTimeout(&I2C_DRIVER, mpu6050_addr, mpu6050_transaction.txbuf, 1, mpu6050_transaction.rxbuf, 1, sensor_i2c_timeout);
	i2cReleaseBus(&I2C_DRIVER);
	printAnyErrors(status);
	rdata = mpu6050_transaction.rxbuf[0];

	printAnyErrors(status);

    return rdata;
}

uint16_t mpu6050_read_double_register(mpu6050_regaddr highAddress, mpu6050_regaddr lowAddress) {

    uint16_t double_register = 0;
    reg_data rdata; // uint8_t

    rdata = mpu6050_read_register(highAddress);
	double_register = rdata << 8;

	rdata = mpu6050_read_register(lowAddress);
	double_register = (double_register | rdata);

    return double_register;
}

void imu_init(void) {

    reg_data rdata; // uint8_t
    
    i2cStart(&I2CD3, &sensor_i2c_config);

	mpu6050_write_register(A_G_PWR_MGMT_1, MPU6050_PM1_RESET);
	chThdSleepMilliseconds(200);  // wait for device reset

    mpu6050_write_register(A_G_SIGNAL_PATH_RESET, 0b111);
	chThdSleepMilliseconds(200);  // wait for signal path reset

	rdata = MPU6050_PM1_X_GYRO_CLOCKREF & (~(MPU6050_PM1_SLEEP));   // make sure device is 'awake'
    mpu6050_write_register(A_G_PWR_MGMT_1, rdata);

	rdata = 16;                                          // 2 ms sample period.
    mpu6050_write_register(A_G_SMPLRT_DIV, rdata);

	rdata = MPU6050_I2C_BYPASS | MPU6050_INT_LEVEL | MPU6050_LATCH_INT_EN;
	mpu6050_write_register(A_G_INT_PIN_CFG, rdata);

    //rdata = MPU6050_I2C_MST_EN;
    //mpu6050_write_register(A_G_USER_CTRL, rdata);

	rdata = MPU6050_A_HPF_RESET | MPU6050_A_SCALE_pm8g;
	mpu6050_write_register(A_G_ACCEL_CONFIG, rdata);

	rdata = MPU6050_G_SCALE_pm500;
	mpu6050_write_register(A_G_GYRO_CONFIG, rdata);

	rdata = MPU6050_INT_EN_DATA_RD_EN;
    mpu6050_write_register(A_G_INT_ENABLE, rdata);

    serial_printString("Successfully configured MPU-9150.");

    mpu6050_write_register(A_G_USER_CTRL, 0b01000000);

    rdata = mpu6050_read_register(A_G_USER_CTRL);
    serial_printInt(rdata);
};

vector3 read_acceleration(void) {
    
	vector3 accel = {
        mpu6050_read_double_register(A_G_ACCEL_XOUT_H, A_G_ACCEL_XOUT_L),   // x
        mpu6050_read_double_register(A_G_ACCEL_YOUT_H, A_G_ACCEL_YOUT_L),   // y
        mpu6050_read_double_register(A_G_ACCEL_ZOUT_H, A_G_ACCEL_ZOUT_L),   // z
    };
    
    return accel;
}

vector3 read_rotation(void) {
    
	vector3 rot = {
        mpu6050_read_double_register(A_G_GYRO_XOUT_H, A_G_GYRO_XOUT_L),   // x
        mpu6050_read_double_register(A_G_GYRO_YOUT_H, A_G_GYRO_YOUT_L),   // y
        mpu6050_read_double_register(A_G_GYRO_ZOUT_H, A_G_GYRO_ZOUT_L),   // z
    };
    
    return rot;
}

vector3 read_magnetic_field(void) {

    akm8975_read_register(MAGN_DEVICE_ID);

    vector3 mag = {
        akm8975_read_register(MAGN_CNTL),   // x
        akm8975_read_register(MAGN_CNTL),   // y
        akm8975_read_register(MAGN_CNTL),   // z
    };
    
	//vector3 mag = {
    //    akm8975_read_double_register(MAGN_HXH, MAGN_HXL),   // x
    //    akm8975_read_double_register(MAGN_HYH, MAGN_HYL),   // y
    //    akm8975_read_double_register(MAGN_HZH, MAGN_HZL),   // z
    //};
        
    return mag;
}

imu_state imu_read_state(void) {
    
    imu_state state = {
        {100, 100, 100},    // gyro
        {100, 100, 100},    // accel
        {100, 100, 100},    // mag
        25,                 // temp
    };

    return state;
}
