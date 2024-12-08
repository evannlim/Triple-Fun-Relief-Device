#include <Arduino.h>
#include <Servo.h>
#include <chrono>

extern float runningAverage;
extern bool lastPressed;

int buttonTickRunningAverage(int buttonPin);

int buttonTickBPM(int buttonPin, int current_intensity_score, int delay_in_ms);