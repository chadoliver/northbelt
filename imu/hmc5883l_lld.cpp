#include "hal.h"
#include "ch.h"
#include "types.h"
#include "sensors.h"
#include "hmc5883l_lld.h"
#include "hmc5883l_register_map.h"

void HMC5883L::HMC5883L (I2CDriver* i2c_instance) {
    
    i2c_driver = i2c_instance;
    
    write_register(HMC5883L_MODE, HMC5883L_CONTINUOUS_MEASUREMENT);
    write_register(HMC5883L_CONFIG_A, HMC5883L_DATA_RATE_75_HZ)
};

void HMC5883L::write_register (hmc5883l_regaddr address, reg_data rdata) {
    Sensor::write_register ((uint8_t) address, rdata)
};

reg_data HMC5883L::read_register(hmc5883l_regaddr address) {
    return Sensor::read_register((uint8_t) address);
};

vector3 HMC5883L::read_measurement(hmc5883l_regaddr address) {
    
    vector3 measurement;
    
    i2c_data received[6] = Sensor::read_register((uint8_t) address, 6);

    measurement.x = (received[0] << 8) | received[1];
    measurement.z = (received[2] << 8) | received[3];       // note that the register order is x, z, y, not the intuitive x, y, z.
    measurement.y = (received[4] << 8) | received[5];
    
    return measurement;
};

vector3 HMC5883L::read_mag(void) {
    return read_measurement(HMC5883L_XOUT_H);
};