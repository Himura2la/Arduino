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

#ifndef MMA7455_h
#define MMA7455_h

#include "Arduino.h"
#include "Wire.h"

class MMA7455 {
  public:
    MMA7455();
    void initSensitivity(int sensitivity);
    byte readAxis(char axis);
  private:
    byte _buffer;
};

#endif
