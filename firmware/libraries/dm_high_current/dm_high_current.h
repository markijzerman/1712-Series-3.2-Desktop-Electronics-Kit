/*
* dm_high_current.h - Library for Device Module 3.2 High Current
* Created By Kevin Lam, June 2, 2017
* Released for Desktop Kit
* Philip Beesley Architect Inc. / Living Architecture Systems Group
*/

#ifndef DM_HIGH_CURRENT_h
#define DM_HIGH_CURRENT_h

#include "Arduino.h"

class DeviceModuleHigh
{
public:
	DeviceModuleHigh();
	void setPinMapping(const int digital_pin_array[], const int analog_pin_array[]);
	void writeActuator(int port_number, int port_state);
	int readAnalog(int port_number);
private:
	int digital_port_pin[8];
	int analog_port_pin[8];

};


#endif