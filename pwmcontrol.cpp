#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>

#include <string>

#include "pwmcontrol.h"

using namespace std;

PwmControl::PwmControl(unsigned char pwmchip, bool negation):ready(false),chip(pwmchip),negation(negation)
{
    const std::string basePath = "/sys/class/pwm";
    const std::string name("pwmchip" + std::to_string(pwmchip));

    std::ofstream exportStream(basePath+"/" + name + "/export");
    if (!exportStream.good())
        cerr << "could not export " << name << endl;
    else
        exportStream << "0" << endl;

    string path = basePath + "/" + name + "/pwm0/period";
    fdPeriod = open(path.c_str(), O_WRONLY);
    if (fdPeriod <= -1)
        cerr << "could not open " << path << endl;


    path = basePath + "/" + name + "/pwm0/duty_cycle";
    fdDutycycly = open(path.c_str(), O_WRONLY);
    if (fdDutycycly <= -1 )
        cerr << "could not open " << path << endl;


    path = basePath + "/" + name + "/pwm0/enable";
    fdOutput = open(path.c_str(), O_WRONLY);
    if (fdOutput <= -1 )
        cerr << "could not open " << path << endl;


    this->ready=true;

    this->setFrequency(100000);
    this->setDutycycly(50000);
    this->setOutput(0);
}


void PwmControl::setFrequency(float frequency)
{
    if (!ready)
        return;
    this->_period = frequency;
    string value(to_string(((unsigned int)frequency)));
    ::write(fdPeriod, value.c_str(), value.length());
}

void PwmControl::setDutycycly(float percent)
{
    if (!ready)
        return;
    unsigned int duty = (this->_period/100*percent);
    if (this->negation)
        duty=this->_period -duty;

    string value(to_string(duty));
    ::write(fdDutycycly, value.c_str(), value.length());
}

void PwmControl::setOutput(bool state)
{
    if (!ready)
        return;

    string value(to_string(((unsigned char)state)));
    ::write(fdOutput, value.c_str(), value.length());
}
