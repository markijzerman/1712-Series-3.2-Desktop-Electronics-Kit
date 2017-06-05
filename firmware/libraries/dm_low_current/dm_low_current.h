/*
* dm_low_current.h - Library for Device Module 3.1 Low Current
* Created By Kevin Lam, June 5, 2017
* Released for Desktop Kit
* Philip Beesley Architect Inc. / Living Architecture Systems Group
*/

#ifndef DM_LOW_CURRENT_h
#define DM_LOW_CURRENT_h

#include "Arduino.h"
#include <SoftwareSerial.h>

class DeviceModuleLow
{
public:
	DeviceModuleLow();
	DeviceModuleLow(int digital_pin_array[], int analog_pin_array[]);
	void writeActuator(int port_number, bool port_state);
	int readAnalog(int port_number);
	
private:
	int digital_port_pin[8];
	int analog_port_pin[8];
	SoftwareSerial serial_port;

};


#endif