#include <gyroscope.hpp>

float gyroscopeSensorTick(Servo servo, const int servoPin) {
  return myImu.readFloatGyroY();
}

int convertAnalogToDegrees(int analogValue) {
    pass;
}
int convertAnalogToIntensity(int analogueValue) {
    pass;
}
