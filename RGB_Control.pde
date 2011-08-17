#include <SPI.h>
#include "RGBController.h"

int redPin = 3;
int greenPin = 5;
int bluePin = 6;

RGBController fader(0, 200);

void setup() {
  Serial.begin(9600);

  fader.configPin(RED, 3, PULSE);
  fader.configPin(GREEN, 5, PULSE);
  fader.configPin(BLUE, 6, PULSE);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  fader.set(RED, 200);
}

void loop() {
  fader.step(GREEN, 1);
  //fader.step(RED, 10);
  //fader.step(BLUE, 50);
  delay(100);
}


