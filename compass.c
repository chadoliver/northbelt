#include "hal.h"
#include "ch.h"
#include "sensor.h"
#include "compass.h"

#define     HMC5883L_MAX_TX_BUFFER                 50
#define     HMC5883L_MAX_RX_BUFFER                 50

const uint8_t hmc5883l_address = 0x1E;

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

typedef struct {
	i2cflags_t i2c_errors;                   // i2cflags_t is a uint32_t
	I2CDriver* i2c_instance;                 /*! which stm32f407 I2C instance to use (there are 3)       */
	i2c_data txbuf[HMC5883L_MAX_TX_BUFFER]; /*! Transmit buffer                                         */
	i2c_data rxbuf[HMC5883L_MAX_RX_BUFFER]; /*! Receive buffer                                          */
} HMC5883L_Driver;

HMC5883L_Driver hmc5883l_driver;

static void compass_write_register(hmc5883l_regaddr address, reg_data rdata) {
	msg_t status = RDY_OK;

	mpu9150_driver.txbuf[0] = address;
	mpu9150_driver.txbuf[1] = rdata;
	i2cAcquireBus(&I2C_DRIVER);
	status = i2cMasterTransmitTimeout(&I2C_DRIVER, hmc5883l_address, hmc5883l_driver.txbuf, 2, hmc5883l_driver.rxbuf, 0, mpu9150_i2c_timeout);
	i2cReleaseBus(&I2C_DRIVER);

	printAnyErrors(status);
}


//================================================================================================//

/*
An Arduino code example for interfacing with the HMC5883

by: Jordan McConnell
 SparkFun Electronics
 created on: 6/30/11
 license: OSHW 1.0, http://freedomdefined.org/OSHW

Analog input 4 I2C SDA
Analog input 5 I2C SCL
*/

#include <Wire.h> //I2C Arduino Library

#define address 0x1E //0011110b, I2C 7bit address of HMC5883

void setup(){
  //Initialize Serial and I2C communications
  Serial.begin(9600);
  Wire.begin();
  
  //Put the HMC5883 IC into the correct operating mode
  Wire.beginTransmission(address); //open communication with HMC5883
  Wire.send(0x02); //select mode register
  Wire.send(0x00); //continuous measurement mode
  Wire.endTransmission();
}

void loop(){
  
  int x,y,z; //triple axis data

  //Tell the HMC5883 where to begin reading data
  Wire.beginTransmission(address);
  Wire.send(0x03); //select register 3, X MSB register
  Wire.endTransmission();
  
 
 //Read data from each axis, 2 registers per axis
  Wire.requestFrom(address, 6);
  if(6<=Wire.available()){
    x = Wire.receive()<<8; //X msb
    x |= Wire.receive(); //X lsb
    z = Wire.receive()<<8; //Z msb
    z |= Wire.receive(); //Z lsb
    y = Wire.receive()<<8; //Y msb
    y |= Wire.receive(); //Y lsb
  }
  
  //Print out values of each axis
  Serial.print("x: ");
  Serial.print(x);
  Serial.print("  y: ");
  Serial.print(y);
  Serial.print("  z: ");
  Serial.println(z);
  
  delay(250);
}
