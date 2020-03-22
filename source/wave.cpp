//#include "Arduino.h"
#include "wave.h"

Wave::Wave(int pin, byte minOutput) {
	pinMode(pin, OUTPUT);
	_pin = pin;
	this->minOutput = minOutput;
}

void Wave::setBrightness(byte brightness) {
	this->brightness = brightness;
}

unsigned int Wave::getStep() {
	return millis()-start;
}

unsigned long Wave::getStart() {
	return start;
}

void Wave::runWave() {
	(this->*currentAnim)();
	if (pinValue < 0.5*minOutput) {
		pinValue = 0;
	} else if (pinValue < minOutput) {
		pinValue = minOutput;
	}
	analogWrite(_pin,pinValue);
		//Serial.println(pinValue);
}




unsigned int Wave::setWave(int wave, int speed, int multiplier, int brightness) {
	switch(wave) {
		case 0: 	currentAnim = &Wave::sine;				break;
		case 1:		currentAnim = &Wave::triangle;			break;
		case 2: 	currentAnim = &Wave::sawTooth;			break;
		case 3:
					currentAnim = &Wave::convex;
					power = random(15,60) / 10.0;
					break;
		case 4: 	currentAnim = &Wave::concave;			break;
		case 5: 	currentAnim = &Wave::square;			break;
		case 6:
					currentAnim = &Wave::wickedSaw1;
					power = random(15,60) / 10.0;
					break;
		case 7:
					currentAnim = &Wave::wickedSaw2;
					power = random(15,60) / 10.0;
					break;
		case 8: 	currentAnim = &Wave::wickedConcave1;	break;
		case 9: 	currentAnim = &Wave::wickedConcave2;	break;
		case 10:	currentAnim = &Wave::stepLadderUp;		break;
		case 11:	currentAnim = &Wave::stepLadderDown;	break;
		case 12:	currentAnim = &Wave::twoLevels;				break;
		case 13:
					currentAnim = &Wave::bounceDown;
					power = -(.0005*multiplier*multiplier) + 0.0299*multiplier + 1.3417;
					break;
		case 14:	currentAnim = &Wave::staccato;				break;
		case 15: 	currentAnim = &Wave::on;							break;
		case 16: 	currentAnim = &Wave::off;							break;
		case OFF: 	currentAnim = &Wave::off;						break;


		default:	currentAnim = &Wave::off;							break;

	}

	this->speed = speed;
	this->multiplier = multiplier;
	this->start = millis();
	this->brightness = brightness;
	return speed * multiplier;
}

// Wave functions

void Wave::sine() {
	int v = ((sin(((2 * PI) / speed) * (getStep()) - (PI / 2.0))) + 1) * brightness / 2;
	pinValue = v;
}

void Wave::triangle() {
	int x = getStep() % speed;
	int v = abs(abs(x - speed / 2.0) / (speed / 2.0) - 1) * brightness;
	pinValue = v;
 }

void Wave::sawTooth() {
	int v = (getStep() % speed / float(speed)) * brightness;
	pinValue = v;
}

void Wave::convex() {
	int x = getStep() % speed;
	int v = pow(abs(((x + speed / 2) % (speed)) - speed / 2) / (speed / 2.0), power) * brightness;
 	pinValue = v;
}

void Wave::concave() {
	int x=getStep() % speed;
	int v = sqrt(abs(((x + speed / 2) % speed) - speed / 2) / (speed / 2.0)) * brightness;
	pinValue = v;
}

void Wave::square() {
	int v = abs((getStep() + speed - speed / 4) % speed) <= (speed / 2.0) ? brightness : 0;
	pinValue = v;
}

void Wave::wickedSaw1() {
	int x=getStep() % speed;
	int tmpSpeed = speed*2;
	int v = pow(abs(((x + tmpSpeed / 2) % (tmpSpeed)) - tmpSpeed / 2) / (tmpSpeed / 2.0), power) * brightness;
	pinValue = v;
}

void Wave::wickedSaw2() {
	int x=getStep() % speed + speed;
	int tmpSpeed = speed*2;
	int v = pow(abs(((x + tmpSpeed / 2) % tmpSpeed) - tmpSpeed / 2) / (tmpSpeed / 2.0), power) * brightness;
	pinValue = v;
}

void Wave::wickedConcave1() {
	int x=getStep() % speed;
	int tmpSpeed = speed*2;
	int v = sqrt(abs(((x + tmpSpeed / 2) % tmpSpeed) - tmpSpeed / 2) / (tmpSpeed / 2.0)) * brightness;
	pinValue = v;
}

void Wave::wickedConcave2() {
	int x=getStep() % speed + speed;
	int tmpSpeed = speed*2;
	int v = sqrt(abs(((x + tmpSpeed / 2) % tmpSpeed) - tmpSpeed / 2) / (tmpSpeed / 2.0)) * brightness;
	pinValue = v;
}

void Wave::stepLadderUp() {
	int x = getStep() % speed;
	int v = (((x*5/speed) + 1) * brightness) / 5;
	pinValue = v;
}

void Wave::stepLadderDown() {
	int x = getStep() % speed;
	int v = (-((((x*5/speed) + 1) * brightness) / 5)) + (brightness * 6 / 5);
	pinValue = v;
}

void Wave::twoLevels() {
	int x = getStep() % speed;
	int v = ((x*2/speed)+1) * (brightness/2);
	pinValue = v;
}

void Wave::bounceDown() {
	int x = getStep();
	int v = ((sin(((2 * PI) / speed) * pow(float(x)/multiplier,power) - (PI / 2.0))) + 1) * brightness / 2 ;//* sqrt((1.0-float(x)/duration));
	pinValue = v;
}

void Wave::staccato() {
	int x = getStep() % speed;
	int v;
	if ((x < speed*4/10) || (x >=speed/2 && x < speed*7/10) || (x >= speed*8/10 && x < speed*9/10)) {
		v = brightness;
	} else {
		v=0;
	}
	pinValue = v;
}

void Wave::on() {
	pinValue = brightness;
}

void Wave::off() {
	pinValue = 0;
}
