#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <cmath>

#include "voltagecontrol.h"
using namespace std;

VoltageControl::VoltageControl(unsigned char device, unsigned char channel)
{
	const string path = "/sys/bus/iio/devices/iio\:device" + to_string(device) + "/in_voltage"+to_string(channel)+"_raw";
	fdVoltage = open(path.c_str(), O_RDONLY);
	if (fdVoltage < -1)
		cerr << "could not open " << path << endl;
	this->ready = true;
}


float VoltageControl::getVoltage()
{
	if (!this->ready)
		return NAN;

	char buffer[16];
	::lseek(fdVoltage,0,SEEK_SET);
	::read(fdVoltage,buffer,sizeof(buffer));

	return strtof(buffer,0);
}
