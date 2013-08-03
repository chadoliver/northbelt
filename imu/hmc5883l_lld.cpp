#include "hal.h"
#include "ch.h"
#include "types.h"
#include "sensors.h"
#include "hmc5883l_lld.h"
#include "hmc5883l_register_map.h"

void HMC5883L::HMC5883L (I2CDriver* i2c_instance, BinarySemaphore* semaphore_instance) {
    
    i2c_driver = i2c_instance;
    
    configure_device();
    
    semaphore = semaphore_instance;
    chSemInit(&semaphore, 0);
};

void HMC5883L::configure_device(void) {
    write_register(HMC5883L_MODE, HMC5883L_CONTINUOUS_MEASUREMENT);
    write_register(HMC5883L_CONFIG_A, HMC5883L_DATA_RATE_75_HZ);
};

void HMC5883L::write_register (hmc5883l_regaddr address, reg_data rdata) {
    Sensor::write_register ((uint8_t) address, rdata)
};

reg_data HMC5883L::read_register(hmc5883l_regaddr address) {
    return Sensor::read_register((uint8_t) address);
};

vector3 HMC5883L::read_mag(void) {
    hmc5883l_regaddr start_addr = HMC5883L_XOUT_H;
    return read_measurement((uint8_t) start_addr);
};
