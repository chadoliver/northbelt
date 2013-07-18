#include "hal.h"
#include "ch.h"

#define I2C_DRIVER I2CD3

typedef uint8_t i2c_data;
typedef uint8_t reg_data;

const systime_t sensor_i2c_timeout = MS2ST(400);

const I2CConfig sensor_i2c_config = {
    OPMODE_I2C,
    400000,                // i2c clock speed, as specified in mpu6050 datasheet.
    FAST_DUTY_CYCLE_2,
};
