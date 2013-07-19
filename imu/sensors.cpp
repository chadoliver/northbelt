#include "hal.h"
#include "ch.h"
#include "types.h"
#include "sensors.h"
#include "serialChannel.h"

virtual Sensor::Sensor(uint8_t address, I2CDriver* i2c_instance) {
    device_address = address;
    i2c_driver = i2c_instance;
};

void Sensor::printAnyErrors (msg_t status) {
    if (status != RDY_OK){
        serial_printString("status:");
        serial_printInt(status);
        serial_printString("i2c_errors:");
        serial_printInt(i2cGetErrors(&i2c_driver));
        serial_printString("");
    }
};

void Sensor::write_register (uint8_t address, reg_data rdata) {
    msg_t status = RDY_OK;
    
    txbuf[0] = [address, rdata];
    i2cAcquireBus(&i2c_driver);
	status = i2cMasterTransmitTimeout(&i2c_driver, device_address, txbuf, 2, rxbuf, 0, i2c_timeout);
	i2cReleaseBus(&i2c_driver);
    
	printAnyErrors(status);
};

reg_data Sensor::read_register(uint8_t address, int rx_bytes) {
    msg_t status = RDY_OK;

    txbuf[0] = address;
	i2cAcquireBus(&i2c_driver);
	status = i2cMasterTransmitTimeout(&i2c_driver, device_address, txbuf, 1, rxbuf, rx_bytes, i2c_timeout);
	i2cReleaseBus(&i2c_driver);
	printAnyErrors(status);

	printAnyErrors(status);
    return rxbuf;
};

void Sensor::wait_for_data(void) {
    
};










