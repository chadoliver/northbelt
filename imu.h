
typedef struct vector3 {
	uint16_t x;
	uint16_t y;
	uint16_t z;
} vector3;

// read data from mpu9150
typedef struct imu_state {
	vector3 rot;
	vector3 accel;
    vector3 mag;
    uint16_t temp;
} imu_state;


void imu_init(void);

vector3 read_acceleration(void);
vector3 read_rotation(void);
vector3 read_magnetic_field(void);

imu_state imu_read_state(void);
