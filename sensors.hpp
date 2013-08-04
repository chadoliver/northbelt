#ifndef SENSORS_H_
#define SENSORS_H_

#include <ch.hpp>
#include <hal.h>
#include <types.hpp>
#include <serialChannel.hpp>

const systime_t i2c_timeout = MS2ST(400);

#define     MAX_TX_BUFFER   50
#define     MAX_RX_BUFFER   50

class Sensor {
    
    protected:
        virtual uint8_t getDeviceAddress(void);
        
        I2CDriver* i2c_driver_ptr;
        reg_data txbuf[MAX_TX_BUFFER];          // Transmit buffer
        reg_data rxbuf[MAX_RX_BUFFER];          // Receive buffer
        SerialChannel serial;
        
        vector3 read_measurement (uint8_t address);
    
    public:
        BinarySemaphore semaphore;

        Sensor(void);
        void init(I2CDriver* i2c_instance);
        void printAnyErrors (msg_t status);
        virtual void configure_device(void);
        virtual void write_register (uint8_t address, reg_data rdata);
        virtual reg_data* read_register(uint8_t address, int rx_bytes);
        void wait_for_data(void);
        void signal_data_ready(void);
};

#endif
