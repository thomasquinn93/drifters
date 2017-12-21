// Written by Thomas Quinn tom@orbinnovations.com
// Property of Orb Innovations
// IMU.cpp - For reading inertial measurement unit (IMU)

// ARDUINO LIBRARIES ----------------------------------------------------------
#include "Arduino.h"
#include <Wire.h>
#include "quaternionFilters.h"
#include "MPU9250.h"

// CUSTOM LIBRARIES -----------------------------------------------------------
#include "OrbIMU.h"

MPU9250 myIMU;

void OrbIMU::begin() {
  Wire.begin();
  delay(1000);
  myIMU.initMPU9250();
  delay(1000);
  myIMU.initAK8963(myIMU.magCalibration);
}

void OrbIMU::readAccel() {
  myIMU.readAccelData(myIMU.accelCount);  // Read the x/y/z adc values
  myIMU.getAres();
}

void OrbIMU::calAccel() {
  // calculate the accleration value into actual g's
  // This depends on scale being set
  myIMU.ax = (float)myIMU.accelCount[0] * myIMU.aRes; // - accelBias[0];
  myIMU.ay = (float)myIMU.accelCount[1] * myIMU.aRes; // - accelBias[1];
  myIMU.az = (float)myIMU.accelCount[2] * myIMU.aRes; // - accelBias[2];
}

void OrbIMU::readGyro() {
  myIMU.readGyroData(myIMU.gyroCount);  // Read the x/y/z adc values
  myIMU.getGres();
}

void OrbIMU::calGyro() {
  // calculate the gyro value into actual degrees per second
  // This depends on scale being set
  myIMU.gx = (float)myIMU.gyroCount[0] * myIMU.gRes;
  myIMU.gy = (float)myIMU.gyroCount[1] * myIMU.gRes;
  myIMU.gz = (float)myIMU.gyroCount[2] * myIMU.gRes;
}

void OrbIMU::readMag() {
  myIMU.readMagData(myIMU.magCount);  // Read the x/y/z adc values
  myIMU.getMres();
}

void OrbIMU::calMag() {
  // environmental x-axis correction in milliGauss, should be
  // automatically calculated
  myIMU.magbias[0] = +470.;
  // User environmental x-axis correction in milliGauss TODO axis??
  myIMU.magbias[1] = +120.;
  // User environmental x-axis correction in milliGauss
  myIMU.magbias[2] = +125.;

  // magnetometer values in milliGauss
  // Include factory calibration per data sheet and user environmental
  // corrections
  // Get actual magnetometer value, this depends on scale being set
  myIMU.mx = (float)myIMU.magCount[0] * myIMU.mRes * myIMU.magCalibration[0] -
  myIMU.magbias[0];
  myIMU.my = (float)myIMU.magCount[1] * myIMU.mRes * myIMU.magCalibration[1] -
  myIMU.magbias[1];
  myIMU.mz = (float)myIMU.magCount[2] * myIMU.mRes * myIMU.magCalibration[2] -
  myIMU.magbias[2];
}

void OrbIMU::getAccel() {
  readAccel();
  calAccel();
}

void OrbIMU::getGyro() {
  readGyro();
  calGyro();
}

void OrbIMU::getMag() {
  readMag();
  calMag();
}

void OrbIMU::quaternion(){
  // Must be called before updating quaternions!
  myIMU.updateTime();

  // Sensors x (y)-axis of the accelerometer is aligned with the y (x)-axis of
  // the magnetometer; the magnetometer z-axis (+ down) is opposite to z-axis
  // (+ up) of accelerometer and gyro! We have to make some allowance for this
  // orientationmismatch in feeding the output to the quaternion filter. For the
  // MPU-9250, we have chosen a magnetic rotation that keeps the sensor forward
  // along the x-axis just like in the LSM9DS0 sensor. This rotation can be
  // modified to allow any convenient orientation convention. This is ok by
  // aircraft orientation standards! Pass gyro rate as rad/s
  //  MadgwickQuaternionUpdate(ax, ay, az, gx*PI/180.0f, gy*PI/180.0f, gz*PI/180.0f,  my,  mx, mz);
  MahonyQuaternionUpdate(myIMU.ax, myIMU.ay, myIMU.az, myIMU.gx * DEG_TO_RAD,
    myIMU.gy * DEG_TO_RAD, myIMU.gz * DEG_TO_RAD, myIMU.my,
    myIMU.mx, myIMU.mz, myIMU.deltat);
  }

  float OrbIMU::accX(){
    return 1000 * myIMU.ax;
  }

  float OrbIMU::accY(){
    return 1000 * myIMU.ay;
  }

  float OrbIMU::accZ(){
    return 1000 * myIMU.az;
  }

  float OrbIMU::gyroX(){
    return myIMU.gx;
  }

  float OrbIMU::gyroY(){
    return myIMU.gy;
  }

  float OrbIMU::gyroZ(){
    return myIMU.gz;
  }

  void OrbIMU::print() {
    // Print acceleration values in milligs!
    Serial.print("X-acc: ");
    Serial.print(1000 * myIMU.ax);
    Serial.print(" mg ");
    Serial.print("Y-acc: ");
    Serial.print(1000 * myIMU.ay);
    Serial.print(" mg ");
    Serial.print("Z-acc ");
    Serial.print(1000 * myIMU.az);
    Serial.println(" mg ");

    // Print gyro values in degree/sec
    Serial.print("X-gyro: ");
    Serial.print(myIMU.gx, 3);
    Serial.print(" deg/sec ");
    Serial.print("Y-gyro: ");
    Serial.print(myIMU.gy, 3);
    Serial.print(" deg/sec ");
    Serial.print("Z-gyro: ");
    Serial.print(myIMU.gz, 3);
    Serial.println(" deg/sec");

    // Print mag values in degree/sec
    // Serial.print("X-mag: ");
    // Serial.print(myIMU.mx);
    // Serial.print(" mG ");
    // Serial.print("Y-mag ");
    // Serial.print(myIMU.my);
    // Serial.print(" mG ");
    // Serial.print("Z-mag: ");
    // Serial.print(myIMU.mz);
    // Serial.println(" mG");

    myIMU.tempCount = myIMU.readTempData();  // Read the adc values
    // Temperature in degrees Centigrade
    myIMU.temperature = ((float) myIMU.tempCount) / 333.87 + 21.0;
    // Print temperature in degrees Centigrade
    Serial.print("Temperature is ");  Serial.print(myIMU.temperature, 1);
    Serial.println(" degrees C");
  }
