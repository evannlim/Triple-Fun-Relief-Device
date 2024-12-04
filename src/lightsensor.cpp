#include <lightsensor.hpp>
/* 
Defines lightSensorTick
Reads intensity from sensor, moves servo to match intensity, outputs intensity as an int
Takes in the servo object and the servo's pin to control the servo
Takes in the light sensor's pin to read from it
*/
int lightSensorTick(const int lightSensorPin) {
  int analogValue = analogRead(lightSensorPin);

  Serial.println(analogValue);
  
  return convertAnalogToIntensity(analogValue);
}

int convertAnalogToIntensity(int analogValue) {
