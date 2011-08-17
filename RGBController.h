#ifndef RGBCONTROLLER_H
#define RGBCONTROLLER_H

#include <SPI.h> //We need it for analogWrite; we're assuming they're using PWM

//Color constants
#define RED 0
#define GREEN 1
#define BLUE 2

#define FADE 0
#define PULSE 1

#define ARRAY_MSIZE = sizeof(int) * 3

class RGBController {
private:
  int minValue;
  int maxValue;
  int *pins;
  int *patterns;
  int *values;
  int *lastValues;
  void updatePin(int);
  int nextStep(int, int);
  int nextPulseStep(int, int);
  int nextFadeStep(int, int);
public:
  RGBController(int=0, int=255); //0-255 is the default.  Some IC can achieve greater variety.
  ~RGBController();
  void configPin(int, int, int=PULSE);
  void step(int, int=1); //default step value of 1
  void set(int, int);
  void reset();
};


#endif
