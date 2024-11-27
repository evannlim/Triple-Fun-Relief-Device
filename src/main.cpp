#include <Arduino.h>
#include <Wire.h>

#include <TFT_eSPI.h>

#include <Servo.h>
#include <SparkFunLSM6DSO.h>
#include <chrono>
#include <iostream>

#include "lightsensor.hpp"

// Objects
TFT_eSPI tft = TFT_eSPI();
Servo myservo;
LSM6DSO myIMU;

// Pins
const int redLedPin = 2;
const int yellowLedPin = 15;
const int blueLedPin = 13;
const int lightSensorPin = 32;
const int servoPin = 25;

// Attributes for printing onto LILYGO screen
const int x_coordinate = 0;
const int y_coordinate = 0;
const int font_size = 50;

int intensityScore;

void setup() {
  Serial.begin(9600);

  // Initialize LILYGO screen
  tft.begin();
  tft.setRotation(0);

  // Set background and font
  tft.setTextSize(font_size);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  // Initialize light sensor
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  pinMode(lightSensorPin, INPUT);
  myservo.attach(servoPin);

  intensityScore = 0;

  for (int i=20; i > -1; --i) {
    if (i % 3 == 0) {
      digitalWrite(redLedPin, HIGH);
      delay(i * i);
      digitalWrite(redLedPin, LOW);
    }
    else if (i % 3 == 1) {
      digitalWrite(yellowLedPin, HIGH);
      delay(i * i);
      digitalWrite(yellowLedPin, LOW);
    }
    else if (i % 3 == 2) {
      digitalWrite(blueLedPin, HIGH);
      delay(i * i);
      digitalWrite(blueLedPin, LOW);
    }
  }
  digitalWrite(yellowLedPin, HIGH);
}

void loop() {
  intensityScore = lightSensorTick(myservo, servoPin, lightSensorPin);
  tft.drawNumber(intensityScore, x_coordinate, y_coordinate);
  delay(100);
}
