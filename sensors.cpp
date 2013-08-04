#include "sensors.hpp"
#include "serialChannel.hpp"

Sensor::Sensor(void) {
    // pass
};

void Sensor::configure_device(void) {
    // pass
};

void Sensor::init(I2CDriver* i2c_instance) {
    
    i2c_driver_ptr = i2c_instance;
    configure_device();
    chBSemInit(&semaphore, 0);
};

uint8_t Sensor::getDeviceAddress(void) {
    return 0;
};

void Sensor::printAnyErrors (msg_t status) {
    if (status != RDY_OK){
        serial.printString("status:");
        serial.printInt(status);
        serial.printString("i2c_errors:");
        serial.printInt(i2cGetErrors(i2c_driver_ptr));
        serial.printString("");
    }
};

void Sensor::write_register (uint8_t address, reg_data rdata) {
    msg_t status = RDY_OK;
    
    txbuf[0] = address;
    txbuf[1] = rdata;
    i2cAcquireBus(i2c_driver_ptr);
	status = i2cMasterTransmitTimeout(i2c_driver_ptr, getDeviceAddress(), txbuf, 2, rxbuf, 0, i2c_timeout);
	i2cReleaseBus(i2c_driver_ptr);
    
	printAnyErrors(status);
};

reg_data* Sensor::read_register(uint8_t address, int rx_bytes) {
    msg_t status = RDY_OK;

    txbuf[0] = address;
	i2cAcquireBus(i2c_driver_ptr);
	status = i2cMasterTransmitTimeout(i2c_driver_ptr, getDeviceAddress(), txbuf, 1, rxbuf, rx_bytes, i2c_timeout);
	i2cReleaseBus(i2c_driver_ptr);
	printAnyErrors(status);

	printAnyErrors(status);
    return rxbuf;
};

void Sensor::wait_for_data(void) {
    chBSemWait(&semaphore);
};

void Sensor::signal_data_ready(void) {   
    chBSemSignal(&semaphore);
};

vector3 Sensor::read_measurement(uint8_t address) {
    
    vector3 measurement;
    
    reg_data* received = Sensor::read_register(address, 6);

    measurement.x = (received[0] << 8) | received[1];
    measurement.y = (received[2] << 8) | received[3];
    measurement.z = (received[4] << 8) | received[5];
    
    return measurement;
};










