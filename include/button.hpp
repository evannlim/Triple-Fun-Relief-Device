#include <Arduino.h>
#include <Servo.h>
#include <chrono>

extern float runningAverage;
extern bool lastPressed;

//int buttonTickRunningAverage(int buttonPin);

int buttonTick(int buttonPin);

void initButtonState();

void calculateButtonIntensityScore();