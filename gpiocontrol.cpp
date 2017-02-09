#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>

#include "gpiocontrol.h"

using namespace std;

GpioControl::GpioControl(unsigned int pinnumber):ready(false)
{
	const string basePath = "/sys/class/gpio";
	const string name("gpio" + to_string(pinnumber));

	std::ofstream exportStream(basePath + "/export");
	if (!exportStream.good()) {
		cerr << "could not export " << name << endl;
	}

	exportStream << to_string(pinnumber) << endl;

	std::ofstream directionStream(basePath + "/" + name + "/direction");
	if (!directionStream.good()) {
		cerr << "could not set direction for " << name << endl;
	}

	directionStream << "out" << endl;

	auto path = basePath + "/" + name + "/value";
	fdPin = open(path.c_str(), O_WRONLY);
	if (fdPin >= 1) {
		ready = true;
	} else {
		cerr << "could not open " << path << endl;
	}
	this->setState(false);

}
void GpioControl::setState(bool state)
{
	string value(to_string(state));
	::write(fdPin, value.c_str(), value.length());
}


void GpioControl::setImpuls(int delay)
{
	if (!ready)
		return;

	this->setState(true);
	if(delay>=0)
		usleep(delay);
	this->setState(false);

}
