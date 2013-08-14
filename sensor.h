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

#define     MAX_TX_BUFFER                 50
#define     MAX_RX_BUFFER                 50

typedef struct {
	i2cflags_t i2c_errors;                   // i2cflags_t is a uint32_t
	I2CDriver* i2c_instance;                 // which stm32f407 I2C instance to use (there are 3)
	i2c_data txbuf[MAX_TX_BUFFER];          // Transmit buffer
	i2c_data rxbuf[MAX_RX_BUFFER];          // Receive buffer
} i2c_Transaction;
