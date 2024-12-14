#include <Arduino.h>
#include <Servo.h>
#include <chrono>

int buttonTick(int buttonPin);
void initButtonState();
void calculateButtonIntensityScore();