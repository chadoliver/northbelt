#ifndef HMC5883L_LLD_H_
#define HMC5883L_LLD_H_

#include "types.h"

class HMC5883L: public Sensor {
    
    private:
        static const uint8_t device_address = 0x1E;
    
    public:
        void HMC5883L (I2CDriver* i2c_instance);
        void write_register (hmc5883l_regaddr address, reg_data rdata);
        reg_data read_register(hmc5883l_regaddr address);   
        vector3 read_measurement(mpu6050_regaddr address);
        vector3 read_mag(void);
        
};

#endif