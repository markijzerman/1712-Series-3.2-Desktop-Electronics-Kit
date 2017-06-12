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
	void writeActuator(char port_char, int port_state);
	int readAnalog(char port_char);
	void setPinMapping(const int digital_pin_array[], const int analog_pin_array[]);

private:
	int digital_port_pin[8];
	int analog_port_pin[8];
};


#endif