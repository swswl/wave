# wave
An Arduino C++ class to generate various wave patterns

Greatly inspired by the ALA led library (https://github.com/bportaluri/ALA). 

# Description
This library allows the generation of several simple and more complex signal patterns to be used as PWM output for the Arduino platform. 

# Usage
## Object creation
`Wave wave(Pin, minOutpout);`

Where:
- Pin: Arduino PWM pin to use as output
- minOutput: A value below which the output will be:
  - = 0 if <50% of this parameter
  - = minOutput if >50% of parameter and <minOutput
## Setting up animation
`duration = wave.setWave(animation, speed, rep, brightness);`

Where:
- animation: one of (currently) 17 (0-16) animations. int
- speed: duration of a single "pass" of the animation (in ms). int
- rep: the number of repetitions (passes) of the animation. int
- brightness: 0-255 max value of PWM. int

Returns:
- duration: speed * rep. unsigned int
