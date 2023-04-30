/*
 * Hstepper.h - Library for controlling a stepper motor
 * Created by Daniel Harley Jordan 2020
*/
//if this is the first time Hstepper.h has been included then Hstepper_h is defined as NOTHING
//then the second time Hstepper.h is included Hstepper.h has already been defined and soo the code isn't ran
#ifndef Hstepper_h
#define Hstepper_h 

//this is the header file for the Stepper package
#include "Arduino.h"

void turn(double degW, bool dir);
void HstepSetup();


#endif 
