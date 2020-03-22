#define Pin 5 //PWM pin for output signal
#include "wave.h"

byte brightness = 255;
Wave wave(Pin, 100);
unsigned int duration;
unsigned int animation;
unsigned long start;

void setup() {
  randomSeed(analogRead(0));
  pinMode(Pin, OUTPUT);
  unsigned long now = millis();
  start = millis();
}

void loop() {
  if (millis() - wave.getStart() < duration) {
    wave.runWave();
  } else {
    // Setting up new animation
    animation = random(0, 17);
    int speed = random(500, 1300);
    int rep = random(15, 15);
    duration = wave.setWave(animation, speed, rep, brightness);
  }
}
