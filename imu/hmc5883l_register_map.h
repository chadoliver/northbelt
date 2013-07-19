#include "sensor.h"


/* Register Map */
typedef enum {
    HMC5883L_CONFIG_A = 0x00,
    HMC5883L_CONFIG_B = 0x01,
    HMC5883L_MODE     = 0x02,
    HMC5883L_XOUT_H   = 0x03,
	HMC5883L_XOUT_L   = 0x04,
	HMC5883L_ZOUT_H   = 0x05,
	HMC5883L_ZOUT_L   = 0x06,
	HMC5883L_YOUT_H   = 0x07,
	HMC5883L_YOUT_L   = 0x08,
    HMC5883L_STATUS   = 0x09,
} hmc5883l_regaddr;


/* Config A Register bits */
#define     HMC5883L_DATA_RATE_0p75_HZ          ((reg_data)(0<<4)) | ((reg_data)(0<<3)) | ((reg_data)(0<<2))
#define     HMC5883L_DATA_RATE_1p5_HZ           ((reg_data)(0<<4)) | ((reg_data)(0<<3)) | ((reg_data)(1<<2))
#define     HMC5883L_DATA_RATE_3_HZ             ((reg_data)(0<<4)) | ((reg_data)(1<<3)) | ((reg_data)(0<<2))
#define     HMC5883L_DATA_RATE_7p5_HZ           ((reg_data)(0<<4)) | ((reg_data)(1<<3)) | ((reg_data)(1<<2))
#define     HMC5883L_DATA_RATE_15_HZ            ((reg_data)(1<<4)) | ((reg_data)(0<<3)) | ((reg_data)(0<<2))
#define     HMC5883L_DATA_RATE_30_HZ            ((reg_data)(1<<4)) | ((reg_data)(0<<3)) | ((reg_data)(1<<2))
#define     HMC5883L_DATA_RATE_75_HZ            ((reg_data)(1<<4)) | ((reg_data)(1<<3)) | ((reg_data)(0<<2))


/* Mode Register bits */
#define     HMC5883L_HIGH_SPEED_I2C             ((reg_data)(1<<7))
#define     HMC5883L_IDLE_MODE                  ((reg_data)(1<<1))
#define     HMC5883L_SINGLE_MEASUREMENT         ((reg_data)(1<<0))
#define     HMC5883L_CONTINUOUS_MEASUREMENT     ((reg_data)(0<<0))