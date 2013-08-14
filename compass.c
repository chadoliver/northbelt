#include "hal.h"
#include "ch.h"
#include "sensor.h"
#include "compass.h"
#include "hmc5883l_register_map.h"

const uint8_t hmc5883l_address = 0x1E;

i2c_Transaction hmc5883l_transaction;

static void compass_write_register(hmc5883l_regaddr address, reg_data rdata) {
	msg_t status = RDY_OK;

	hmc5883l_transaction.txbuf[0] = address;
	hmc5883l_transaction.txbuf[1] = rdata;
	i2cAcquireBus(&I2C_DRIVER);
	status = i2cMasterTransmitTimeout(&I2C_DRIVER, hmc5883l_address, hmc5883l_driver.txbuf, 2, hmc5883l_driver.rxbuf, 0, mpu9150_i2c_timeout);
	i2cReleaseBus(&I2C_DRIVER);

	printAnyErrors(status);
}

reg_data akm8975_read_register(hmc5883l_regaddr address) {

    msg_t status = RDY_OK;
    reg_data rdata = 0;

	hmc5883l_transaction.txbuf[0] = address;
	i2cAcquireBus(&I2C_DRIVER);
	status = i2cMasterTransmitTimeout(&I2C_DRIVER, akm8975_addr, hmc5883l_transaction.txbuf, 1, hmc5883l_transaction.rxbuf, 1, sensor_i2c_timeout);
	i2cReleaseBus(&I2C_DRIVER);
	printAnyErrors(status);
	rdata = hmc5883l_transaction.rxbuf[0];

	printAnyErrors(status);

    return rdata;
}

uint16_t akm8975_read_double_register(hmc5883l_regaddr highAddress, hmc5883l_regaddr lowAddress) {

    uint16_t double_register = 0;
    reg_data rdata; // uint8_t

    rdata = akm8975_read_register(highAddress);
	double_register = rdata << 8;

	rdata = akm8975_read_register(lowAddress);
	double_register = (double_register | rdata);

    return double_register;
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
