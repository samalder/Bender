/*
Bender.h - Library for operating a wire bending module, part of the Mini-Bender
Created by Sam D. Alder, 02/09/2014
*/
#ifndef Bender_h
#define Bender_h

#include "Arduino.h"

class Bender
{
  public:
    Bender(int, int, int);
    void on();
    void off();
    void setTimeStep(int);
    void setDirection(int);
    void update();
    void setBendAngle(int);
    void setSolenoid(int);
    
    //State Machine Variables
    int timeStep;
    float bendAngle;
    bool solenoidOn;
    
  private:
  	//Pin Map
    int _bendStepPin;
    int _bendDirPin;
    int _solenoidPin;
    
    //State Machine Variables
    bool _moving;
    int _bendDirection;
    
    //Operational Variables (Carry over)
    int _lastTime;
    int _bendStepPinState;
    	//Motion and wire tracking
    double _stepCount;
    double _stepCountTotal;
    
};

#endif
