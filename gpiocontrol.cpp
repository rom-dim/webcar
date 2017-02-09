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

/*
DebugPin::DebugPin(std::string number, int delay) :
	ready(false),
	delay(delay) {
		const string basePath = "/sys/class/gpio";
		const string name("gpio" + number);

		std::ofstream exportStream(basePath + "/export");
		if (!exportStream.good()) {
			cerr << "could not export " << name << endl;
		}

		exportStream << number << endl;

		std::ofstream directionStream(basePath + "/" + name + "/direction");
		if (!directionStream.good()) {
			cerr << "could not set direction for " << name << endl;
		}

		directionStream << "out" << endl;

		auto path = basePath + "/" + name + "/value";
		fd = open(path.c_str(), O_WRONLY);
		if (fd >= 1) {
			ready = true;
		} else {
			cerr << "could not open " << path << endl;
		}

		gpioBuf[1] = 0;
}

DebugPin::DebugPin(std::string number) :
	DebugPin(number, 0) {
}

void DebugPin::toggle() {
	if (!ready)
		return;

	gpioBuf[0] = '1';
	::write(fd, gpioBuf, 2);
	gpioBuf[0] = '0';
	::write(fd, gpioBuf, 2);
}

void DebugPin::set(bool en) {
	if (!ready)
		return;

	static unsigned int delayCounter = 0;
	if (delayCounter < delay) {
		delayCounter++;
	} else {
		gpioBuf[0] = en ? '1' : '0';
		::write(fd, gpioBuf, 2);

		delayCounter = 0;
	}
}*/
