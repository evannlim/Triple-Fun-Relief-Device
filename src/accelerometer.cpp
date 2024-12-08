#include <accelerometer.hpp>

int accelSensorTick(LSM6DSO myIMU) {
  float accelReading = myIMU.readFloatAccelY();
  return convertAccelReadingToIntensity(accelReading);
}

int convertAccelReadingToIntensity(float accelReading) {
    return abs(accelReading * 100);
}
