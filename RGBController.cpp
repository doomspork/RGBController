#include "RGBController.h"

/*
  RGBController.cpp - Library managaging RGB LED patterns without delays()
  Created by doomspork, August 15, 2011.
  Released into the public domain.
*/

RGBController::RGBController(int min, int max) {
  pins_ = (int *)malloc(sizeof(int) * 3) ;
  patterns_ = (int *)malloc(sizeof(int) * 3);
  callbacks_ = (callback *)malloc(sizeof(callback *) * 3);
  BOUNDS b;
  b.min = min;
  b.max = max;
  bounds_ = b;
  this->reset();
}

RGBController::~RGBController() {
  free(pins_);
  free(values_);
  free(lastValues_);
  free(callback_);
}

void RGBController::updatePin(int pin) {
  analogWrite(pins_[pin], values_[pin]);
}

int RGBController::nextStep(int pin, int steps) {
  return callbacks_[pin](last, current, steps, bounds);
}

void RGBController::configPin(int color, int pin, callback func) {
  this->pins_[color] = pin;
  this->callbacks_[color] = func;
}

void RGBController::set(int pin, int value) {
  lastValues_[pin] = values[pin];
  values_[pin] = value;
  updatePin(pin);
}

void RGBController::step(int pin, int steps) {
  this->set(pin, this->nextStep(pin, steps));
}

void RGBController::reset() {
  free(values_);
  values_ = (int *)malloc(sizeof(int) * 3);
  values_[0] = minValue;
  values_[1] = minValue;
  values_[2] = minValue;
  free(lastValues_);
  lastValues_ = (int *)malloc(sizeof(int) * 3);
  lastValues_[0] = minValue;
  lastValues_[1] = minValue;
  lastValues_[2] = minValue;
}

int RGBController::fade(int last, int current, int steps, BOUNDS bound) {
  int future;
  if(current < maxValue) {
    future = current + steps;
  } else {
    future = 0;
  }
}

int RGBController::pulse(int last, int current, int steps, BOUNDS bound) {
  int future;
  if((current > last && current < bound.max) || current <= bound.min) {
    future = current + steps;
  } else {
    future = current - steps;
  }
  return future;
}
