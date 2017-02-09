#ifndef CARCONTROL_H
#define CARCONTROL_H

#include <thread>
#include <iostream>

#include "voltagecontrol.h"
#include "pwmcontrol.h"
#include "gpiocontrol.h"

class CarControl
{
public:
	CarControl();
	void setSpeed (float speed);
    void setWheels (float position);
    void setMaxSpeed (float multiplier);

private:
	PwmControl* pwm4;
    PwmControl* pwm5;

	float _speed;
    float _wheelspos;
    float _multiplier;
};

#endif // CARCONTROL_H
