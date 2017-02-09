#include <math.h>
#include <thread>
#include <iostream>
#include <stdio.h>
#include <unistd.h>

using namespace std;

#include "pwmcontrol.h"
#include "voltagecontrol.h"
#include "carcontrol.h"


CarControl::CarControl():_multiplier(1.0f)
{
    pwm4 = new PwmControl(3);

    pwm5 = new PwmControl(4);

    pwm4->setFrequency(20000000);
    pwm5->setFrequency(20000000);

    setWheels(0);
	setSpeed(0);

	pwm4->setOutput(true);
    pwm5->setOutput(true);
}

void CarControl::setSpeed(float speed)
{
    float max = 9;
    float min = 6;

    _speed=((((max-min)/200)*speed*-1) +min+((max-min)/2));

    pwm4->setDutycycly(_speed*_multiplier);
}

void CarControl::setWheels(float position)
{
    float max = 9;
    float min = 6;

    _wheelspos=((((max-min)/200)*position*-1) +min+((max-min)/2));

    pwm5->setDutycycly(_wheelspos);
}

void CarControl::setMaxSpeed(float multiplier)
{
    if(multiplier>1)
        multiplier=1.0f;
    if(multiplier<-1)
        multiplier=-1.0f;
    
    _multiplier = multiplier;
}
