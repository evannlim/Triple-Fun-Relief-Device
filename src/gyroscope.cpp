#include <gyroscope.hpp>

float gyroscopeSensorTick(Servo servo, const int servoPin, LSM6DSO myImu) {
  return myImu.readFloatGyroY();
}

int gyroscopeConvertAnalogToDegrees(int analogValue) {
    return -1;
}
int gyroscopeConvertonvertAnalogToIntensity(int analogueValue) {
    return -1;
}
