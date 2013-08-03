#ifndef TYPES_H_
#define TYPES_H_

typedef uint8_t i2c_data;
typedef uint8_t reg_data;

typedef struct vector3 {
    uint16_t x;
    uint16_t y;
    uint16_t z;
} vector3;

class imu_state {
    public:
        vector3 rot;
        vector3 accel;
        vector3 mag;
};

#endif