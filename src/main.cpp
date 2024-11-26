#include <Arduino.h>

#include <TFT_eSPI.h>

#include <Servo.h>
#include <chrono>
#include <iostream>

// Objects
TFT_eSPI tft = TFT_eSPI();
Servo myservo;

// Number coordinates
const int x_coordinate = 0;
const int y_coordinate = 0;
const int font_size = 50;

void setup() {
  Serial.begin(9600);

  // Initialize LILYGO screen
  tft.begin();
  tft.setRotation(0);

  // Set background and font
  tft.setTextSize(font_size);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
}

void loop() {
  tft.drawNumber(0, x_coordinate, y_coordinate);
  delay(200);
}
