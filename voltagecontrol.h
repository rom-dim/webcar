#ifndef VOLTAGECONTROL_H
#define VOLTAGECONTROL_H


class VoltageControl
{
public:
	VoltageControl(unsigned char device, unsigned char channel);
	float getVoltage();

private:
	int fdVoltage;
	bool ready;
};

#endif // VOLTAGECONTROL_H
