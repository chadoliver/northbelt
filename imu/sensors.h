#ifndef SENSORS_H_
#define SENSORS_H_

#include "types.h"

const systime_t i2c_timeout = MS2ST(400);

#define     MAX_TX_BUFFER   50
#define     MAX_RX_BUFFER   50

class Sensor {
    
    protected:
        virtual uint8_t device_address;
        I2CDriver* i2c_driver;
        i2c_data txbuf[MAX_TX_BUFFER];          // Transmit buffer
        i2c_data rxbuf[MAX_RX_BUFFER];          // Receive buffer
    
    public:
        virtual Sensor::Sensor(uint8_t address, I2CDriver* i2c_instance);
        void printAnyErrors (msg_t status);
        void write_register (uint8_t address, reg_data rdata);
        reg_data read_register(uint8_t address, int rx_bytes);
        void wait_for_data(void);
};

#endif