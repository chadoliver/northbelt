#include "hal.h"
#include "ch.h"
#include "serialChannel.h"
#include "imu.h"

typedef uint8_t mpu9150_i2c_data;
typedef uint8_t reg_data;

#define I2C_DRIVER I2CD3

#define     MPU9150_MAX_TX_BUFFER                 50
#define     MPU9150_MAX_RX_BUFFER                 50

/*! register 55 INT pin/Bypass */
#define     MPU9150_CLKOUT_EN                     ((reg_data)(1<<0))
#define     MPU9150_I2C_BYPASS                    ((reg_data)(1<<1))
#define     MPU9150_FSCYNC_INT_EN                 ((reg_data)(1<<2))
#define     MPU9150_FSCYNC_INT_LEVEL              ((reg_data)(1<<3))
#define     MPU9150_INT_RD_CLEAR                  ((reg_data)(1<<4))
#define     MPU9150_LATCH_INT_EN                  ((reg_data)(1<<5))
#define     MPU9150_INT_OPEN                      ((reg_data)(1<<6))
#define     MPU9150_INT_LEVEL                     ((reg_data)(1<<7))

/*! register 106 User Control */
#define     MPU9150_SIG_COND_RESET                ((reg_data)(1<<0))
#define     MPU9150_I2C_MST_RESET                 ((reg_data)(1<<1))
#define     MPU9150_FIFO_RESET                    ((reg_data)(1<<2))
#define     MPU9150_I2C_MST_EN                    ((reg_data)(1<<5))

/*! register 107 Power management 1 */
#define     MPU9150_PM1_X_GYRO_CLOCKREF           ((reg_data)(1<<0))
#define     MPU9150_PM1_SLEEP                     ((reg_data)(1<<6))
#define     MPU9150_PM1_RESET                     ((reg_data)(1<<7))
#define     MPU9150_INT_EN_DATA_RD_EN             ((reg_data)(1<<0))

typedef enum mpu9150_a_g_regaddr {
	A_G_SELF_TEST_X        = 0x0D,
    A_G_SELF_TEST_Y        = 0x0E,
    A_G_SELF_TEST_Z        = 0x0F,
    A_G_SELF_TEST_A        = 0x10,
    A_G_SMPLRT_DIV         = 0x19,
    A_G_CONFIG             = 0x1A,
    A_G_GYRO_CONFIG        = 0x1B,
    A_G_ACCEL_CONFIG       = 0x1C,
    A_G_FF_THR             = 0x1D,
    A_G_FF_DUR             = 0x1E,
    A_G_MOT_THR            = 0x1F,
    A_G_MOT_DUR            = 0x20,
    A_G_ZRMOT_THR          = 0x21,
    A_G_ZRMOT_DUR          = 0x22,
    A_G_FIFO_EN            = 0x23,
    A_G_I2C_MST_CTRL       = 0x24,
    A_G_I2C_SLV0_ADDR      = 0x25,
    A_G_I2C_SLV0_REG       = 0x26,
    A_G_I2C_SLV0_CTRL      = 0x27,
    A_G_I2C_SLV1_ADDR      = 0x28,
    A_G_I2C_SLV1_REG       = 0x29,
    A_G_I2C_SLV1_CTRL      = 0x2A,
    A_G_I2C_SLV2_ADDR      = 0x2B,
    A_G_I2C_SLV2_REG       = 0x2C,
    A_G_I2C_SLV2_CTRL      = 0x2D,
    A_G_I2C_SLV3_ADDR      = 0x2E,
    A_G_I2C_SLV3_REG       = 0x2F,
    A_G_I2C_SLV3_CTRL      = 0x30,
    A_G_I2C_SLV4_ADDR      = 0x31,
    A_G_I2C_SLV4_REG       = 0x32,
    A_G_I2C_SLV4_DO        = 0x33,
    A_G_I2C_SLV4_CTRL      = 0x34,
    A_G_I2C_SLV4_DI        = 0x35,
    A_G_I2C_MST_STATUS     = 0x36,
    A_G_INT_PIN_CFG        = 0x37,
    A_G_INT_ENABLE         = 0x38,
    A_G_INT_STATUS         = 0x3A,
    A_G_ACCEL_XOUT_H       = 0x3B,
    A_G_ACCEL_XOUT_L       = 0x3C,
    A_G_ACCEL_YOUT_H       = 0x3D,
    A_G_ACCEL_YOUT_L       = 0x3E,
    A_G_ACCEL_ZOUT_H       = 0x3F,
    A_G_ACCEL_ZOUT_L       = 0x40,
    A_G_TEMP_OUT_H         = 0x41,
    A_G_TEMP_OUT_L         = 0x42,
    A_G_GYRO_XOUT_H        = 0x43,
    A_G_GYRO_XOUT_L        = 0x44,
    A_G_GYRO_YOUT_H        = 0x45,
    A_G_GYRO_YOUT_L        = 0x46,
    A_G_GYRO_ZOUT_H        = 0x47,
    A_G_GYRO_ZOUT_L        = 0x48,
    A_G_EXT_SENS_DATA_00   = 0x49,
    A_G_EXT_SENS_DATA_01   = 0x4A,
    A_G_EXT_SENS_DATA_02   = 0x4B,
    A_G_EXT_SENS_DATA_03   = 0x4C,
    A_G_EXT_SENS_DATA_04   = 0x4D,
    A_G_EXT_SENS_DATA_05   = 0x4E,
    A_G_EXT_SENS_DATA_06   = 0x4F,
    A_G_EXT_SENS_DATA_07   = 0x50,
    A_G_EXT_SENS_DATA_08   = 0x51,
    A_G_EXT_SENS_DATA_09   = 0x52,
    A_G_EXT_SENS_DATA_10   = 0x53,
    A_G_EXT_SENS_DATA_11   = 0x54,
    A_G_EXT_SENS_DATA_12   = 0x55,
    A_G_EXT_SENS_DATA_13   = 0x56,
    A_G_EXT_SENS_DATA_14   = 0x57,
    A_G_EXT_SENS_DATA_15   = 0x58,
    A_G_EXT_SENS_DATA_16   = 0x59,
    A_G_EXT_SENS_DATA_17   = 0x5A,
    A_G_EXT_SENS_DATA_18   = 0x5B,
    A_G_EXT_SENS_DATA_19   = 0x5C,
    A_G_EXT_SENS_DATA_20   = 0x5D,
    A_G_EXT_SENS_DATA_21   = 0x5E,
    A_G_EXT_SENS_DATA_22   = 0x5F,
    A_G_EXT_SENS_DATA_23   = 0x60,
    A_G_MOT_DETECT_STATUS  = 0x61,
    A_G_I2C_SLV0_D0        = 0x63,
    A_G_I2C_SLV1_D0        = 0x64,
    A_G_I2C_SLV2_DO        = 0x65,
    A_G_I2C_SLV3_DO        = 0x66,
    A_G_I2C_MST_DELAY_CTRL = 0x67,
    A_G_SIGNAL_PATH_RESET  = 0x68,
    A_G_MOT_DETECT_CTRL    = 0x69,
    A_G_USER_CTRL          = 0x6A,
    A_G_PWR_MGMT_1         = 0x6B,
    A_G_PWR_MGMT_2         = 0x6C,
    A_G_FIFO_COUNTH        = 0x72,
    A_G_FIFO_COUNTL        = 0x73,
    A_G_FIFO_R_W           = 0x74,
    A_G_WHO_AM_I           = 0x75 
} mpu9150_reg_addr;

typedef enum {
	MAGN_DEVICE_ID         = 0x00,
	MAGN_INFORMATION       = 0x01,
	MAGN_STATUS_1          = 0x02,
	MAGN_HXL               = 0x03,
	MAGN_HXH               = 0x04,
	MAGN_HYL               = 0x05,
	MAGN_HYH               = 0x06,
	MAGN_HZL               = 0x07,
	MAGN_HZH               = 0x08,
	MAGN_STATUS_2          = 0x09,
	MAGN_CNTL              = 0x0A,
	MAGN_ASTC              = 0x0C,
	MAGN_TS1               = 0x0D,
	MAGN_TS2               = 0x0E,
	MAGN_I2C_DIS           = 0x0F,
	MAGN_ASAX              = 0x10,
	MAGN_ASAY              = 0x11,
	MAGN_ASAZ              = 0x12
} akm8975_reg_addr;

// \typedef Accel High Pass Filter
typedef enum mpu9150_accel_hpf {
	MPU9150_A_HPF_RESET  = 0b000,//!< MPU9150_A_HPF_RESET
	MPU9150_A_HPF_5HZ    = 0b001,//!< MPU9150_A_HPF_5HZ
	MPU9150_A_HPF_2p5HZ  = 0b010,//!< MPU9150_A_HPF_2p5HZ
	MPU9150_A_HPF_1p25HZ = 0b011,//!< MPU9150_A_HPF_1p25HZ
	MPU9150_A_HPF_0p63HZ = 0b100,//!< MPU9150_A_HPF_0p63HZ
	MPU9150_A_HPF_HOLD   = 0b111 //!< MPU9150_A_HPF_HOLD
} mpu9150_accel_hpf;

// \typedef Accel Full Scale
typedef enum mpu9150_accel_scale {
	MPU9150_A_SCALE_pm2g   = (0b00 << 3),//!< MPU9150_A_SCALE_pm2g
	MPU9150_A_SCALE_pm4g   = (0b01 << 3),//!< MPU9150_A_SCALE_pm4g
	MPU9150_A_SCALE_pm8g   = (0b10 << 3),//!< MPU9150_A_SCALE_pm8g
	MPU9150_A_SCALE_pm16g  = (0b11 << 3) //!< MPU9150_A_SCALE_pm16g
} mpu9150_accel_scale;

// \typedef Gyro Full Scale
typedef enum mpu9150_gyro_scale {
	MPU9150_G_SCALE_pm250   = (0b00 << 3),//!< MPU9150_G_SCALE_pm250
	MPU9150_G_SCALE_pm500   = (0b01 << 3),//!< MPU9150_G_SCALE_pm500
	MPU9150_G_SCALE_pm1000  = (0b10 << 3),//!< MPU9150_G_SCALE_pm1000
	MPU9150_G_SCALE_pm2000  = (0b11 << 3) //!< MPU9150_G_SCALE_pm2000
} mpu9150_gyro_scale;

// \typedef Structure for keeping track of an MPU9150 transaction
typedef struct MPU9150_Driver {
	i2cflags_t i2c_errors;                   // i2cflags_t is a uint32_t
	I2CDriver* i2c_instance;                 /*! which stm32f407 I2C instance to use (there are 3)       */
	mpu9150_i2c_data txbuf[MPU9150_MAX_TX_BUFFER]; /*! Transmit buffer                                         */
	mpu9150_i2c_data rxbuf[MPU9150_MAX_RX_BUFFER]; /*! Receive buffer                                          */
} MPU9150_Driver;

MPU9150_Driver mpu9150_driver;

const systime_t mpu9150_i2c_timeout = MS2ST(400);
const uint8_t mpu9150_addr = 0x68;    // See page 8 , MPU9150 Register Map and Descriptions r4.0
const uint8_t akm8975_addr = 0x0C;    // See page 28, MPU9150 Product Specification r4.0

const I2CConfig mpu9150_config = {
    OPMODE_I2C,
    400000,                // i2c clock speed, as specified in mpu9150 datasheet.
    FAST_DUTY_CYCLE_2,
};

static void printAnyErrors(msg_t status) {
	if (status != RDY_OK){
        serial_printString("status:");
        serial_printInt(status);
        serial_printString("i2c_errors:");
        serial_printInt(i2cGetErrors(&I2C_DRIVER));
        serial_printString("");
	}
}

static void akm8975_write_register(akm8975_reg_addr address, reg_data rdata) {
	msg_t status = RDY_OK;

	mpu9150_driver.txbuf[0] = address;
	mpu9150_driver.txbuf[1] = rdata;
	i2cAcquireBus(&I2C_DRIVER);
	status = i2cMasterTransmitTimeout(&I2C_DRIVER, akm8975_addr, mpu9150_driver.txbuf, 2, mpu9150_driver.rxbuf, 0, mpu9150_i2c_timeout);
	i2cReleaseBus(&I2C_DRIVER);

	printAnyErrors(status);
}

reg_data akm8975_read_register(akm8975_reg_addr address) {

    msg_t status = RDY_OK;
    reg_data rdata = 0;

	mpu9150_driver.txbuf[0] = address;
	i2cAcquireBus(&I2C_DRIVER);
	status = i2cMasterTransmitTimeout(&I2C_DRIVER, akm8975_addr, mpu9150_driver.txbuf, 1, mpu9150_driver.rxbuf, 1, mpu9150_i2c_timeout);
	i2cReleaseBus(&I2C_DRIVER);
	printAnyErrors(status);
	rdata = mpu9150_driver.rxbuf[0];

	printAnyErrors(status);

    return rdata;
}

uint16_t akm8975_read_double_register(akm8975_reg_addr highAddress, akm8975_reg_addr lowAddress) {

    uint16_t double_register = 0;
    reg_data rdata; // uint8_t

    rdata = akm8975_read_register(highAddress);
	double_register = rdata << 8;

	rdata = akm8975_read_register(lowAddress);
	double_register = (double_register | rdata);

    return double_register;
}

static void mpu9150_write_register(mpu9150_reg_addr address, reg_data rdata) {
	msg_t status = RDY_OK;

	mpu9150_driver.txbuf[0] = address;
	mpu9150_driver.txbuf[1] = rdata;
	i2cAcquireBus(&I2C_DRIVER);
	status = i2cMasterTransmitTimeout(&I2C_DRIVER, mpu9150_addr, mpu9150_driver.txbuf, 2, mpu9150_driver.rxbuf, 0, mpu9150_i2c_timeout);
	i2cReleaseBus(&I2C_DRIVER);

	printAnyErrors(status);
}

reg_data mpu9150_read_register(mpu9150_reg_addr address) {

    msg_t status = RDY_OK;
    reg_data rdata = 0;

	mpu9150_driver.txbuf[0] = address;
	i2cAcquireBus(&I2C_DRIVER);
	status = i2cMasterTransmitTimeout(&I2C_DRIVER, mpu9150_addr, mpu9150_driver.txbuf, 1, mpu9150_driver.rxbuf, 1, mpu9150_i2c_timeout);
	i2cReleaseBus(&I2C_DRIVER);
	printAnyErrors(status);
	rdata = mpu9150_driver.rxbuf[0];

	printAnyErrors(status);

    return rdata;
}

uint16_t mpu9150_read_double_register(mpu9150_reg_addr highAddress, mpu9150_reg_addr lowAddress) {

    uint16_t double_register = 0;
    reg_data rdata; // uint8_t

    rdata = mpu9150_read_register(highAddress);
	double_register = rdata << 8;

	rdata = mpu9150_read_register(lowAddress);
	double_register = (double_register | rdata);

    return double_register;
}

void imu_init(void) {

    reg_data rdata; // uint8_t
    
    i2cStart(&I2CD3, &mpu9150_config);

	mpu9150_write_register(A_G_PWR_MGMT_1, MPU9150_PM1_RESET);
	chThdSleepMilliseconds(200);  // wait for device reset

    mpu9150_write_register(A_G_SIGNAL_PATH_RESET, 0b111);
	chThdSleepMilliseconds(200);  // wait for signal path reset

	rdata = MPU9150_PM1_X_GYRO_CLOCKREF & (~(MPU9150_PM1_SLEEP));   // make sure device is 'awake'
    mpu9150_write_register(A_G_PWR_MGMT_1, rdata);

	rdata = 16;                                          // 2 ms sample period.
    mpu9150_write_register(A_G_SMPLRT_DIV, rdata);

	rdata = MPU9150_I2C_BYPASS | MPU9150_INT_LEVEL | MPU9150_LATCH_INT_EN;
	mpu9150_write_register(A_G_INT_PIN_CFG, rdata);

    //rdata = MPU9150_I2C_MST_EN;
    //mpu9150_write_register(A_G_USER_CTRL, rdata);

	rdata = MPU9150_A_HPF_RESET | MPU9150_A_SCALE_pm8g;
	mpu9150_write_register(A_G_ACCEL_CONFIG, rdata);

	rdata = MPU9150_G_SCALE_pm500;
	mpu9150_write_register(A_G_GYRO_CONFIG, rdata);

	rdata = MPU9150_INT_EN_DATA_RD_EN;
    mpu9150_write_register(A_G_INT_ENABLE, rdata);

    serial_printString("Successfully configured MPU-9150.");

    mpu9150_write_register(A_G_USER_CTRL, 0b01000000);

    rdata = mpu9150_read_register(A_G_USER_CTRL);
    serial_printInt(rdata);
};

vector3 read_acceleration(void) {
    
	vector3 accel = {
        mpu9150_read_double_register(A_G_ACCEL_XOUT_H, A_G_ACCEL_XOUT_L),   // x
        mpu9150_read_double_register(A_G_ACCEL_YOUT_H, A_G_ACCEL_YOUT_L),   // y
        mpu9150_read_double_register(A_G_ACCEL_ZOUT_H, A_G_ACCEL_ZOUT_L),   // z
    };
    
    return accel;
}

vector3 read_rotation(void) {
    
	vector3 rot = {
        mpu9150_read_double_register(A_G_GYRO_XOUT_H, A_G_GYRO_XOUT_L),   // x
        mpu9150_read_double_register(A_G_GYRO_YOUT_H, A_G_GYRO_YOUT_L),   // y
        mpu9150_read_double_register(A_G_GYRO_ZOUT_H, A_G_GYRO_ZOUT_L),   // z
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
