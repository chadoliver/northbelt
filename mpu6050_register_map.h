#include "sensor.h"

/*! register 55 INT pin/Bypass */
#define     MPU6050_CLKOUT_EN                     ((reg_data)(1<<0))
#define     MPU6050_I2C_BYPASS                    ((reg_data)(1<<1))
#define     MPU6050_FSCYNC_INT_EN                 ((reg_data)(1<<2))
#define     MPU6050_FSCYNC_INT_LEVEL              ((reg_data)(1<<3))
#define     MPU6050_INT_RD_CLEAR                  ((reg_data)(1<<4))
#define     MPU6050_LATCH_INT_EN                  ((reg_data)(1<<5))
#define     MPU6050_INT_OPEN                      ((reg_data)(1<<6))
#define     MPU6050_INT_LEVEL                     ((reg_data)(1<<7))

/*! register 106 User Control */
#define     MPU6050_SIG_COND_RESET                ((reg_data)(1<<0))
#define     MPU6050_I2C_MST_RESET                 ((reg_data)(1<<1))
#define     MPU6050_FIFO_RESET                    ((reg_data)(1<<2))
#define     MPU6050_I2C_MST_EN                    ((reg_data)(1<<5))

/*! register 107 Power management 1 */
#define     MPU6050_PM1_X_GYRO_CLOCKREF           ((reg_data)(1<<0))
#define     MPU6050_PM1_SLEEP                     ((reg_data)(1<<6))
#define     MPU6050_PM1_RESET                     ((reg_data)(1<<7))
#define     MPU6050_INT_EN_DATA_RD_EN             ((reg_data)(1<<0))

typedef enum mpu6050_regaddr {
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
} mpu6050_regaddr;

// \typedef Accel High Pass Filter
typedef enum mpu6050_accel_hpf {
	MPU6050_A_HPF_RESET  = 0b000,//!< MPU6050_A_HPF_RESET
	MPU6050_A_HPF_5HZ    = 0b001,//!< MPU6050_A_HPF_5HZ
	MPU6050_A_HPF_2p5HZ  = 0b010,//!< MPU6050_A_HPF_2p5HZ
	MPU6050_A_HPF_1p25HZ = 0b011,//!< MPU6050_A_HPF_1p25HZ
	MPU6050_A_HPF_0p63HZ = 0b100,//!< MPU6050_A_HPF_0p63HZ
	MPU6050_A_HPF_HOLD   = 0b111 //!< MPU6050_A_HPF_HOLD
} mpu6050_accel_hpf;

// \typedef Accel Full Scale
typedef enum mpu6050_accel_scale {
	MPU6050_A_SCALE_pm2g   = (0b00 << 3),//!< MPU6050_A_SCALE_pm2g
	MPU6050_A_SCALE_pm4g   = (0b01 << 3),//!< MPU6050_A_SCALE_pm4g
	MPU6050_A_SCALE_pm8g   = (0b10 << 3),//!< MPU6050_A_SCALE_pm8g
	MPU6050_A_SCALE_pm16g  = (0b11 << 3) //!< MPU6050_A_SCALE_pm16g
} mpu6050_accel_scale;

// \typedef Gyro Full Scale
typedef enum mpu6050_gyro_scale {
	MPU6050_G_SCALE_pm250   = (0b00 << 3),//!< MPU6050_G_SCALE_pm250
	MPU6050_G_SCALE_pm500   = (0b01 << 3),//!< MPU6050_G_SCALE_pm500
	MPU6050_G_SCALE_pm1000  = (0b10 << 3),//!< MPU6050_G_SCALE_pm1000
	MPU6050_G_SCALE_pm2000  = (0b11 << 3) //!< MPU6050_G_SCALE_pm2000
} mpu6050_gyro_scale;
