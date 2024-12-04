#include <gyroscope.hpp>

float gyroscopeSensorTick(LSM6DSO myIMU) {
  return myIMU.readFloatGyroY();
}

int convertAnalogToIntensity(int analogueValue) {
    return 0;
}
