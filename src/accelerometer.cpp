#include <accelerometer.hpp>

int accelSensorTick(LSM6DSO myIMU) {
  float accelXReading = abs(myIMU.readFloatAccelX());
  float accelYReading = abs(myIMU.readFloatAccelY());
  if (accelXReading > accelYReading)
    return convertAccelReadingToIntensity(accelXReading);
  else
    return convertAccelReadingToIntensity(accelYReading);
}

int convertAccelReadingToIntensity(float accelReading) {
    return accelReading * 100;
}
