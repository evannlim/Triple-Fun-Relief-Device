#include <gyroscope.hpp>

float gyroscopeSensorTick(LSM6DSO myIMU) {
  int gyroReading = myIMU.readFloatGyroY();
  return convertGyroReadingToIntensity(gyroReading);
}

int convertGyroReadingToIntensity(int gyroReading) {
    return gyroReading;
}
