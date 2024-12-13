#include <button.hpp>

bool stillPressed;

int tickCounter;
int lastPressTick;

int previousDuration;
int currentDuration;

int buttonIntensityScore;

// Must be run each time before button game
void initButtonState()
{
  stillPressed = false;

  tickCounter = -1;
  lastPressTick = -1;

  previousDuration = -1;
  currentDuration = -1;

  buttonIntensityScore = 0;
}

int buttonTick(int buttonPin) {
  ++tickCounter;
  bool pressed = not digitalRead(buttonPin);
  if (pressed) {
    // check if it's a new button pressed or still being held from the previous press
    if (not stillPressed) {
      stillPressed = true;

      if (lastPressTick < 0)  // first time button is pressed, lastPressTick doesn't exist yet
      {
        // will do lastPressTick = tickCounter at the end
      }
      else if (previousDuration < 0) // second time button is pressed, previousDuration doesn't exist yet
      {
        previousDuration = tickCounter - lastPressTick;
      }
      else
      {
        currentDuration = tickCounter - lastPressTick;
        calculateButtonIntensityScore();
        previousDuration = currentDuration;
      }
      lastPressTick = tickCounter;
    }
  }
  else {    // if (not pressed)
    stillPressed = false;

    // if the button is not pressed for a long enough period
    if(tickCounter - lastPressTick > 19)
      buttonIntensityScore = 0;
  }

  return buttonIntensityScore;
}

// assigns calculated score to buttonIntensityScore
void calculateButtonIntensityScore()
{
  int avgDuration = (previousDuration + currentDuration) / 2;

  Serial.println(avgDuration);

  if (avgDuration > 70)
    avgDuration = 70;
  else if (avgDuration < 10)
    avgDuration = 10;
  
  buttonIntensityScore = map(avgDuration, 10, 70, 100, 0);
}

/*
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
*/