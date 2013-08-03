#include "hal.h"
#include "ch.h"
#include "types.h"
#include "sensors.h"
#include "serialChannel.h"

void Sensor::Sensor (I2CDriver* i2c_instance, BinarySemaphore* semaphore_instance) {
    
    i2c_driver = i2c_instance;
    
    configure_device(); // This is a virtual method implemented by child classes.
    
    semaphore = semaphore_instance;
    chSemInit(&semaphore, 0);
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
    chBSemWait(semaphore);
};

void Sensor::signal_data_ready(EXTDriver *extp, expchannel_t channel) {
    (void)extp;
    (void)channel;
    
    chBSemSignal(semaphore);
};

vector3 Sensor::read_measurement(uint8_t address) {
    
    vector3 measurement;
    
    i2c_data received[6] = Sensor::read_register(address, 6);

    measurement.x = (received[0] << 8) | received[1];
    measurement.y = (received[2] << 8) | received[3];
    measurement.z = (received[4] << 8) | received[5];
    
    return measurement;
};










