#include <lightsensor.hpp>
/* 
Defines lightSensorTick
Reads intensity from sensor, moves servo to match intensity, outputs intensity as an int
Takes in the servo object and the servo's pin to control the servo
Takes in the light sensor's pin to read from it
*/
int lightSensorTick(Servo servo, const int servoPin, const int lightSensorPin) {
  int analogValue = analogRead(lightSensorPin);

  Serial.println(analogValue);

  return convertAnalogToIntensity(analogValue);
}

int convertAnalogToDegrees(int analogValue) {
  return 180 * (analogValue - minLightSensorValue) / (maxLightSensorValue - minLightSensorValue + 1);
}

int convertAnalogToIntensity(int analogValue) {
  return 100 * (analogValue - minLightSensorValue) / (maxLightSensorValue - minLightSensorValue + 1);
}