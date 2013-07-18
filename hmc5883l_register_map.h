#include "sensor.h"

typedef enum {
    MAGN_CONFIG_A = 0x00,
    MAGN_CONFIG_B = 0x01,
	MAGN_MODE     = 0x02,
    MAGN_HXH      = 0x03,
	MAGN_HXL      = 0x04,
	MAGN_HZH      = 0x05,
	MAGN_HZL      = 0x06,
	MAGN_HYH      = 0x07,
	MAGN_HYL      = 0x08,
    MAGN_STATUS   = 0x09,
} hmc5883l_regaddr;
