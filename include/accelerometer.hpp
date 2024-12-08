#include <SparkFunLSM6DSO.h>
#include <Arduino.h>

//Function Declarations
int accelSensorTick(LSM6DSO myIMU);
int convertAccelReadingToIntensity(float accelReading);
