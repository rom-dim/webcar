#ifndef GPIOCONTROL_H
#define GPIOCONTROL_H


class GpioControl
{
public:
	GpioControl(unsigned int pinnumber);
	void setImpuls(int delay);
	void setState(bool state);

private:
	int fdPin;
	bool ready;
};

#endif // GPIOCONTROL_H
