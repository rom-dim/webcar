#ifndef PWMCONTROL_H
#define PWMCONTROL_H


#include <string>

class PwmControl
{
public:
    PwmControl(unsigned char pwmchip, bool negation=false);
	void setFrequency(float frequency);
	void setDutycycly(float percent);
	void setOutput(bool state);


private:
	unsigned char chip;
	unsigned int _period;

	int fdPeriod;
	int fdDutycycly;
	int fdOutput;
	bool ready;

    bool negation;
};

#endif // PWMCONTROL_H
