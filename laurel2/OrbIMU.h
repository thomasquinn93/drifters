// Written by Thomas Quinn tom@orbinnovations.com
// Property of Orb Innovations
// IMU.cpp - For reading inertial measurement unit (IMU)

#ifndef OrbIMU_h
#define OrbIMU_h

#include "Arduino.h"

class OrbIMU
{
  public:
    void begin();
    void readAccel();
    void calAccel();
    void readGyro();
    void calGyro();
    void readMag();
    void calMag();
    void getAccel();
    void getGyro();
    void getMag();
    void quaternion();
    float accX();
    float accY();
    float accZ();
    float gyroX();
    float gyroY();
    float gyroZ();
    void print();
  private:

};

#endif
