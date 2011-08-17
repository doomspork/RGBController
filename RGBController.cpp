#include "RGBController.h"

RGBController::RGBController(int min, int max) {
  pins = (int *)malloc(ARRAY_MSIZE);
  patterns = (int *)malloc(ARRAY_MSIZE);
  minValue = min;
  maxValue = max;
  this->reset();
}

RGBController::~RGBController() {
  free(pins);
  free(patterns);
  free(values);
  free(lastValues);
}

void RGBController::updatePin(int pin) {
  analogWrite(pins[pin], values[pin]);
}

int RGBController::nextStep(int pin, int steps) {
  switch(this->patterns[pin]) {
    case FADE:
    return this->nextFadeStep(pin, steps);
    case PULSE:
    return this->nextPulseStep(pin, steps);
  }
  return -1; //error!
}

int RGBController::nextPulseStep(int pin, int steps) {
  int current = this->values[pin];
  int last = this->lastValues[pin];
  int future;
  if((current > last && current < maxValue) || current <= minValue) {
    future = current + steps;
  } else {
    future = current - steps;
  }
  return future;
}

int RGBController::nextFadeStep(int pin, int steps) {
  int current = this->values[pin];
  int last = this->lastValues[pin];
  int future;
  if(current < maxValue) {
    future = current + steps;
  } else {
    future = 0;
  }
  return future;  
}

void RGBController::configPin(int color, int pin, int pattern) {
  this->pins[color] = pin;
  this->patterns[color] = pattern;
}

void RGBController::set(int pin, int value) {
  lastValues[pin] = values[pin];
  values[pin] = value;
  updatePin(pin);
}

void RGBController::step(int pin, int steps) {
  this->set(pin, this->nextStep(pin, steps));
}

void RGBController::reset() {
  free(this->values);
  this->values = (int *)malloc(ARRAY_MSIZE);
  this->values[0] = minValue;
  this->values[1] = minValue;
  this->values[2] = minValue;
  free(this->lastValues);
  this->lastValues = (int *)malloc(ARRAY_MSIZE);
  this->lastValues[0] = minValue;
  this->lastValues[1] = minValue;
  this->lastValues[2] = minValue;
}
