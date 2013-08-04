#include <hmc5883l_lld.hpp>

void HMC5883L::configure_device(void) {
    write_register(HMC5883L_MODE, HMC5883L_CONTINUOUS_MEASUREMENT);
    write_register(HMC5883L_CONFIG_A, HMC5883L_DATA_RATE_75_HZ);
};

uint8_t HMC5883L::getDeviceAddress(void) {
    return device_address;
};

void HMC5883L::write_register (hmc5883l_regaddr address, reg_data rdata) {
    Sensor::write_register ((uint8_t) address, rdata);
};

reg_data* HMC5883L::read_register(hmc5883l_regaddr address, int rx_bytes) {
    return Sensor::read_register((uint8_t) address, rx_bytes);
};

vector3 HMC5883L::read_mag(void) {
    hmc5883l_regaddr start_addr = HMC5883L_XOUT_H;
    return read_measurement((uint8_t) start_addr);
};
