#ifndef HMC5883L_LLD_H_
#define HMC5883L_LLD_H_

#include <ch.hpp>
#include <hal.h>
#include <types.hpp>
#include <sensors.hpp>
#include <hmc5883l_register_map.hpp>

class HMC5883L: public Sensor {
    
    private:
        static const uint8_t device_address = 0x1E;
        
        void configure_device(void);
        uint8_t getDeviceAddress(void);
    
    public:
        
        void write_register (hmc5883l_regaddr address, reg_data rdata);
        reg_data* read_register(hmc5883l_regaddr address, int rx_bytes);   
        vector3 read_mag(void);
};

#endif
