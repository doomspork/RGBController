/*
  RGBController.h - Library managaging RGB LED patterns without delays()
  Created by doomspork, August 15, 2011.
  Released into the public domain.
*/

#ifndef RGBCONTROLLER_H
#define RGBCONTROLLER_H

#include <WProgram.h> //We need it for analogWrite; we're assuming they're using PWM

//Color constants
#define RED 0
#define GREEN 1
#define BLUE 2

// Define the callback signature for patterns
// Callbacks are passed three ints: last state, current state, steps, and bounds
// The calculated future step should be returned from the callback
typedef int (*callback)(int, int, int, BOUNDS);

//Shortcuts for the included callbacks
#define PULSE RGBController::pulse
#define FADE RGBController::fade

//Simple container for the bounds
struct BOUNDS {
  int min;
  int max;
}

class RGBController {
private:
  BOUNDS *bounds_;
  int *pins_;
  int *patterns_;
  int *values_;
  int *lastValues_;
  callback *callbacks_;
  void updatePin(int);
  int nextStep(int, int);
public:
  RGBController(int=0, int=255); //0-255 is the default.  Some IC can achieve greater variety.
  ~RGBController();
  void configPin(int, int, callback);
  void step(int, int=1); //default step value of 1
  void set(int, int);
  void reset();
  static int fade(int, int, int, BOUNDS);
  static int pulse(int, int, int, BOUNDS);
};


#endif
