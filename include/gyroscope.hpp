#include <SparkFunLSM6DSO.h>
#include <Arduino.h>

//Function Declarations
float gyroscopeSensorTick(LSM6DSO myIMU);
int convertGyroReadingToIntensity(int analogueValue);
