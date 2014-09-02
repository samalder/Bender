/*
Bender.cpp - Library for operating a wire bend module, part of the Mini-Bender
 Created by Sam D. Alder, 02/09/2014.
*/

#include "Arduino.h"
#include "Bender.h"

Bender::Bender(int bendStepPin, int bendDirPin, int solenoidPin)
{
  	//Save Pin Map
  	_bendStepPin = bendStepPin;
  	_bendDirPin = bendDirPin;
  	_solenoidPin = solenoidPin;
  
  	//Initializing...
	//Output Pins
  	pinMode(_bendStepPin, OUTPUT);
  	pinMode(_bendDirPin, OUTPUT);
  	pinMode(_solenoidPin, OUTPUT);

	//Public Variables
	//---State Machine
	timeStep = 20;
	bendAngle = 0;
	solenoidOn = false;
	
	//Private Variables
	//---State Machine  
  	_moving = false;
  	_bendDirection = 1;
  	
  	//---Carry over
  	_lastTime = 0;
  	_bendStepPinState = 0;
  	_stepCount = 0;
  	_stepCountTotal = 0;

}

void Bender::on()
{
 	_moving = true;
}

void Bender::off()
{
//Update the odometer and clear the step counter
 _stepCountTotal += _stepCount;									//Track motor usage
 _stepCount = 0;												//Reset for next time
 _moving = false;
}

void Bender::update()
{
  if (_stepCount >= bendAngle) {
  	off();
  	bendAngle = 0;
  }
  if (_moving) {
  	int thisTime = millis();
  	int elapsedTime = thisTime - _lastTime;
  	
  	if (elapsedTime > timeStep) {
	    	if (_bendStepPinState > 0) {
    		  digitalWrite(_bendStepPin, LOW);
    		  _bendStepPinState = 0;
    		  _stepCount++;
    		  
    		  _lastTime = thisTime;				//start a new time step
    		}
    		if (_bendStepPinState < 1) {
    		  digitalWrite(_bendStepPin, HIGH);
    		  _bendStepPinState = 1;
    		  _stepCount++;
    		  
    		  _lastTime = thisTime;				//start a new time step
    		}
    	}
  }
}

void Bender::setTimeStep(int timeStepIn) {
	timeStep = timeStepIn;
}

void Bender::setDirection(int bendDirection) {
	_bendDirection = bendDirection;
	digitalWrite(_bendDirPin, _bendDirection);
}

void Bender::setBendAngle(int inputBendAngle) {
	bendAngle = inputBendAngle;
}

void Bender::setSolenoid(int solenoidInput) {
	digitalWrite(_solenoidPin, solenoidInput);
	if (solenoidInput > 0) {solenoidOn = true;}
	else if (solenoidInput < 1) {solenoidOn = false;}
}