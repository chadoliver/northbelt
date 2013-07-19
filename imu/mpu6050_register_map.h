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
	MPU6050_SELF_TEST_X        = 0x0D,
    MPU6050_SELF_TEST_Y        = 0x0E,
    MPU6050_SELF_TEST_Z        = 0x0F,
    MPU6050_SELF_TEST_A        = 0x10,
    MPU6050_SMPLRT_DIV         = 0x19,
    MPU6050_CONFIG             = 0x1A,
    MPU6050_GYRO_CONFIG        = 0x1B,
    MPU6050_ACCEL_CONFIG       = 0x1C,
    MPU6050_FF_THR             = 0x1D,
    MPU6050_FF_DUR             = 0x1E,
    MPU6050_MOT_THR            = 0x1F,
    MPU6050_MOT_DUR            = 0x20,
    MPU6050_ZRMOT_THR          = 0x21,
    MPU6050_ZRMOT_DUR          = 0x22,
    MPU6050_FIFO_EN            = 0x23,
    MPU6050_I2C_MST_CTRL       = 0x24,
    MPU6050_I2C_SLV0_ADDR      = 0x25,
    MPU6050_I2C_SLV0_REG       = 0x26,
    MPU6050_I2C_SLV0_CTRL      = 0x27,
    MPU6050_I2C_SLV1_ADDR      = 0x28,
    MPU6050_I2C_SLV1_REG       = 0x29,
    MPU6050_I2C_SLV1_CTRL      = 0x2A,
    MPU6050_I2C_SLV2_ADDR      = 0x2B,
    MPU6050_I2C_SLV2_REG       = 0x2C,
    MPU6050_I2C_SLV2_CTRL      = 0x2D,
    MPU6050_I2C_SLV3_ADDR      = 0x2E,
    MPU6050_I2C_SLV3_REG       = 0x2F,
    MPU6050_I2C_SLV3_CTRL      = 0x30,
    MPU6050_I2C_SLV4_ADDR      = 0x31,
    MPU6050_I2C_SLV4_REG       = 0x32,
    MPU6050_I2C_SLV4_DO        = 0x33,
    MPU6050_I2C_SLV4_CTRL      = 0x34,
    MPU6050_I2C_SLV4_DI        = 0x35,
    MPU6050_I2C_MST_STATUS     = 0x36,
    MPU6050_INT_PIN_CFG        = 0x37,
    MPU6050_INT_ENABLE         = 0x38,
    MPU6050_INT_STATUS         = 0x3A,
    MPU6050_ACCEL_XOUT_H       = 0x3B,
    MPU6050_ACCEL_XOUT_L       = 0x3C,
    MPU6050_ACCEL_YOUT_H       = 0x3D,
    MPU6050_ACCEL_YOUT_L       = 0x3E,
    MPU6050_ACCEL_ZOUT_H       = 0x3F,
    MPU6050_ACCEL_ZOUT_L       = 0x40,
    MPU6050_TEMP_OUT_H         = 0x41,
    MPU6050_TEMP_OUT_L         = 0x42,
    MPU6050_GYRO_XOUT_H        = 0x43,
    MPU6050_GYRO_XOUT_L        = 0x44,
    MPU6050_GYRO_YOUT_H        = 0x45,
    MPU6050_GYRO_YOUT_L        = 0x46,
    MPU6050_GYRO_ZOUT_H        = 0x47,
    MPU6050_GYRO_ZOUT_L        = 0x48,
    MPU6050_EXT_SENS_DATA_00   = 0x49,
    MPU6050_EXT_SENS_DATA_01   = 0x4A,
    MPU6050_EXT_SENS_DATA_02   = 0x4B,
    MPU6050_EXT_SENS_DATA_03   = 0x4C,
    MPU6050_EXT_SENS_DATA_04   = 0x4D,
    MPU6050_EXT_SENS_DATA_05   = 0x4E,
    MPU6050_EXT_SENS_DATA_06   = 0x4F,
    MPU6050_EXT_SENS_DATA_07   = 0x50,
    MPU6050_EXT_SENS_DATA_08   = 0x51,
    MPU6050_EXT_SENS_DATA_09   = 0x52,
    MPU6050_EXT_SENS_DATA_10   = 0x53,
    MPU6050_EXT_SENS_DATA_11   = 0x54,
    MPU6050_EXT_SENS_DATA_12   = 0x55,
    MPU6050_EXT_SENS_DATA_13   = 0x56,
    MPU6050_EXT_SENS_DATA_14   = 0x57,
    MPU6050_EXT_SENS_DATA_15   = 0x58,
    MPU6050_EXT_SENS_DATA_16   = 0x59,
    MPU6050_EXT_SENS_DATA_17   = 0x5A,
    MPU6050_EXT_SENS_DATA_18   = 0x5B,
    MPU6050_EXT_SENS_DATA_19   = 0x5C,
    MPU6050_EXT_SENS_DATA_20   = 0x5D,
    MPU6050_EXT_SENS_DATA_21   = 0x5E,
    MPU6050_EXT_SENS_DATA_22   = 0x5F,
    MPU6050_EXT_SENS_DATA_23   = 0x60,
    MPU6050_MOT_DETECT_STATUS  = 0x61,
    MPU6050_I2C_SLV0_D0        = 0x63,
    MPU6050_I2C_SLV1_D0        = 0x64,
    MPU6050_I2C_SLV2_DO        = 0x65,
    MPU6050_I2C_SLV3_DO        = 0x66,
    MPU6050_I2C_MST_DELAY_CTRL = 0x67,
    MPU6050_SIGNAL_PATH_RESET  = 0x68,
    MPU6050_MOT_DETECT_CTRL    = 0x69,
    MPU6050_USER_CTRL          = 0x6A,
    MPU6050_PWR_MGMT_1         = 0x6B,
    MPU6050_PWR_MGMT_2         = 0x6C,
    MPU6050_FIFO_COUNTH        = 0x72,
    MPU6050_FIFO_COUNTL        = 0x73,
    MPU6050_FIFO_R_W           = 0x74,
    MPU6050_WHO_AM_I           = 0x75 
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
