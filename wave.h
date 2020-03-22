
#ifndef Wave_h
#define Wave_h
#include "Arduino.h"

#define OFF 99


class Wave
{
public:
	Wave(int pin, byte minOutput);
	unsigned long getStart();
	void setBrightness(byte brightness);
	unsigned int setWave(int wave, int speed, int multiplier, int brightness);
	void runWave();

private:
	// variables
	int _pin;
	unsigned long start;
	int speed;
	int brightness;
	int pinValue;
	int multiplier;
	unsigned int duration;
	float power;
	byte minOutput;	// minimum value of analogWrite
									// values below 0.5 of this will be pulled down to 0
									// values above 0.5 of this, but lower than it, will
									// be pulled up to this value.

	void (Wave::*currentAnim)();

	// util functions
	unsigned int getStep();

	// wave functions
	void sine();
	void triangle();
	void sawTooth();
	void convex();
	void concave();
	void square();
	void wickedSaw1();
	void wickedSaw2();
	void wickedConcave1();
	void wickedConcave2();
	void stepLadderUp();
	void stepLadderDown();
	void twoLevels();
	void bounceDown();
	void staccato();
	void raisedSquare();
	void on();
	void off();
};


#endif
