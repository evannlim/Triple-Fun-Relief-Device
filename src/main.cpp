#include <Arduino.h>
#include <Wire.h>

#include <TFT_eSPI.h>

#include <Servo.h>
#include <SparkFunLSM6DSO.h>
#include <chrono>
#include <iostream>

#include "servo.hpp"
#include "lightsensor.hpp"
#include "button.hpp"
#include "accelerometer.hpp"

// Objects
TFT_eSPI tft = TFT_eSPI(); // 135 x 240 resolution
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

  // Initialize LED bulbs
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);

  // Initialize light sensor and pin
  pinMode(lightSensorPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  myservo.attach(servoPin);

  // Initialize accelerometer board
  Wire.begin();
  if( myIMU.begin() )
    Serial.println("Ready.");
  else { 
    Serial.println("Could not connect to IMU.");
    Serial.println("Freezing");
    while(1)
      delay(2000);
  }
  if( myIMU.initialize(BASIC_SETTINGS) ) // was HARD_INT_SETTINGS before
    Serial.println("Settings Loaded.");

  intensityScore = 0;
}
///*
void loop() {
  game_done = false;
  ticksInGoalScore = 0;
  rndm_game_choice = random(3);
  auto startTime = std::chrono::steady_clock::now();
  initButtonState();

  digitalWrite(blueLedPin, LOW);
  digitalWrite(redLedPin, LOW);
  digitalWrite(yellowLedPin, LOW);

  // Fun startup sequence
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

  // Show target intensity on screen
  goal_intensity_score = random(6, 101);
  tft.fillScreen(TFT_BLACK);
  tft.drawNumber(goal_intensity_score, x_coordinate, y_coordinate);

  while (not game_done) {
    switch (rndm_game_choice) {
      //Button game
      case 0:
        digitalWrite(blueLedPin, HIGH);
        intensityScore = buttonTick(buttonPin);
        break;
      //Light sensor game
      case 1:
        digitalWrite(yellowLedPin, HIGH);
        intensityScore = lightSensorTick(lightSensorPin);
        break;
      //Accelerometer game
      case 2:
        digitalWrite(redLedPin, HIGH);
        intensityScore = accelSensorTick(myIMU);
        break;
    }

    /*
    // Display measured intensity score on screen
    tft.fillRect(0, 60, 135, 50, TFT_BLACK);
    tft.drawNumber(intensityScore, x_coordinate, y_coordinate + 60);
    */

    // Display measured intensity score on servo motor
    myservo.write(convertIntensityToDegrees(intensityScore));

    // Check if measured intensity score meets target intensity score for 100 game ticks
    if (intensityScore >= goal_intensity_score - 5 and intensityScore <= goal_intensity_score + 5) {
      ticksInGoalScore++;
      if (ticksInGoalScore >= 100) {
        game_done = true;
        auto elapsedTime = std::chrono::steady_clock::now() - startTime;
        tft.drawString("Ya!", x_coordinate, y_coordinate + 60);
      }
    }
    else {
      ticksInGoalScore = 0;
    }

    delay(10); // ticks are every 10 miliseconds
  }
}
//*/

/*
// Light Sensor Test: lightSensorTick
// Accelerometer Test: accelSensorTick
void loop() {
  intensityScore = accelSensorTick(myIMU);
  tft.fillScreen(TFT_SKYBLUE);
  tft.drawNumber(intensityScore, x_coordinate, y_coordinate);
  delay(100);
}
*/