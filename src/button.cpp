#include <button.hpp>

extern float runningAverage = 0;
extern bool lastPressed = 1;

const float decayRate = 0.98;
const int gain_per_press = 4;

const int reset_time_in_ms = 1000;
const int beat_time_interval_in_ms = 30000;

extern int last_press_timestamp = 0;
extern int tick_counter = -1;
extern bool firstRun = true;

//Calculates Beats per 30 seconds
int buttonTickBPM(int buttonPin, int current_intensity_score, int delay_in_ms) {
  tick_counter++;
  bool pressed = not digitalRead(buttonPin);
  int intensity_score_return;
  if (firstRun) {
    firstRun = false;
    last_press_timestamp = tick_counter;
    if (pressed) {
      intensity_score_return = 100;
    }
    else {
      intensity_score_return = 0;
    }
  }
  else if (not pressed) {
    if (delay_in_ms * (tick_counter - last_press_timestamp) >= reset_time_in_ms) {
      intensity_score_return = 0;
    }
    else {
      intensity_score_return = current_intensity_score;
    }
  }
  else if (pressed and lastPressed) {
    //Ignore input incase they didn't take finger off
    return current_intensity_score;
  }
  else if (pressed and not lastPressed) {
    //get elapsed milliseconds in ticks from last press, convert to beat per 30 seconds
    int elapsed_time = delay_in_ms * (tick_counter - last_press_timestamp);
    intensity_score_return = beat_time_interval_in_ms / elapsed_time;
    last_press_timestamp = tick_counter;
  }
  lastPressed = pressed;
  if (intensity_score_return > 100) {
    intensity_score_return = 100;
  }
  delay(delay_in_ms);
  return intensity_score_return;
}

int buttonTickRunningAverage(int buttonPin) {
    bool pressed = not digitalRead(buttonPin);
    if (not pressed) {
        runningAverage = runningAverage * decayRate;
    }
    else if (pressed and lastPressed) {
        runningAverage = runningAverage * decayRate;
    }
    else if (pressed and (not lastPressed)) {
        runningAverage = runningAverage * decayRate + gain_per_press;
    }
    if (runningAverage > 100) {
        runningAverage = 100;
    }
    lastPressed = pressed;
    return runningAverage;
}