// MMA7455.cpp - 3 Axis Accelerometer Library
// Moritz Kemper, IAD Physical Computing Lab
// moritz.kemper@zhdk.ch
// ZHdK, 03/04/2012
//
// Glagolev Vladislav, Tula State University
// glagol15@gmail.com
// Himura, 15.02.2015
//
// Released under Creative Commons Licence

#include "MMA7455.h"

#define MMA7455_ADDRESS 0x1D //I2C Adsress for the sensor
#define MMA7455_MODE_CONTROLL 0x16 //Call the sensors Mode Control

#define MMA7455_2G_MODE 0x05 //Set Sensitivity to 2g
#define MMA7455_4G_MODE 0x09 //Set Sensitivity to 4g
#define MMA7455_8G_MODE 0x01 //Set Sensitivity to 8g

#define X_OUT 0x06 //Register for reading the X-Axis
#define Y_OUT 0x07 //Register for reading the Y-Axis
#define Z_OUT 0x08 //Register for reading the Z-Axis
    
MMA7455::MMA7455() { 
  Wire.begin();
}

void MMA7455::initSensitivity(int sensitivity) {
  Wire.beginTransmission(MMA7455_ADDRESS);
  Wire.write(MMA7455_MODE_CONTROLL);
  switch(sensitivity){
    case 2:
      Wire.write(MMA7455_2G_MODE);  //Set Sensitivity to 2g Detection
      break;
    case 4:
      Wire.write(MMA7455_4G_MODE);  //Set Sensitivity to 4g Detection
      break;
    case 8:
      Wire.write(MMA7455_8G_MODE);  //Set Sensitivity to 8g Detection
  }
  Wire.endTransmission();
}

byte MMA7455::readAxis(char axis) {
  Wire.beginTransmission(MMA7455_ADDRESS);
    if(axis == 'x' || axis == 'X') Wire.write(X_OUT);
    if(axis == 'y' || axis == 'Y') Wire.write(Y_OUT);
    if(axis == 'z' || axis == 'Z') Wire.write(Z_OUT);
  Wire.endTransmission();

  Wire.requestFrom(MMA7455_ADDRESS, 1);
  _buffer = Wire.read();
  
  return _buffer;
}