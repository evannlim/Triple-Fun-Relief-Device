#include <Arduino.h>
#include <Wire.h>

#include <TFT_eSPI.h>

#include <Servo.h>
#include <SparkFunLSM6DSO.h>
#include <chrono>
#include <iostream>

#include "lightsensor.hpp"
#include "button.hpp"

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
const int buttonPin = 33;

// Attributes for printing onto LILYGO screen
const int x_coordinate = 0;
const int y_coordinate = 0;
const int font_size = 50;

// Game variables
int intensityScore;
int rndm_game_choice;
int goal_intensity_score;
int ticksInGoalScore;
bool game_done;

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
  pinMode(buttonPin, INPUT_PULLUP);
  myservo.attach(servoPin);

  intensityScore = 0;
}

void loop() {
  game_done = false;
  ticksInGoalScore = 0;
  rndm_game_choice = random(0,2);
  auto startTime = std::chrono::steady_clock::now();

  goal_intensity_score = random(0, 100);

  tft.drawNumber(goal_intensity_score, x_coordinate, y_coordinate);

  digitalWrite(blueLedPin, LOW);
  digitalWrite(redLedPin, LOW);
  digitalWrite(yellowLedPin, LOW);

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

  while (not game_done) {
    rndm_game_choice = 0;
    switch (rndm_game_choice) {
      //Button game
      case 0:
        digitalWrite(blueLedPin, HIGH);
        intensityScore = buttonTickBPM(buttonPin, intensityScore, 20);
        break;
      //Light sensor game
      case 1:
        digitalWrite(yellowLedPin, HIGH);
        //intensityScore = lightSensorTick(myservo, servoPin, lightSensorPin);
        delay(50);
        break;
      //Gyroscope game
      case 2:
        digitalWrite(redLedPin, HIGH);
        //intensityScore = gyroscopeSensorTick(myservo, servoPin, lightSensorPin);
        game_done = true;
        delay(2000);
        break;
    }

    tft.fillScreen(TFT_BLACK);
    tft.drawNumber(goal_intensity_score, x_coordinate, y_coordinate);
    tft.drawNumber(intensityScore, x_coordinate, y_coordinate + 60);
    if (intensityScore >= goal_intensity_score - 2 and intensityScore <= goal_intensity_score + 2) {
      ticksInGoalScore++;
      if (ticksInGoalScore >= 20) {
        game_done = true;
        auto elapsedTime = std::chrono::steady_clock::now() - startTime;
        tft.drawNumber(999, x_coordinate, y_coordinate + 60);
      }
    }
    else {
      ticksInGoalScore = 0;
    }
  }
}
