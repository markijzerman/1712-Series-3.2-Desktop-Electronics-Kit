/*
* dm_high_current.h - Library for Device Module 3.2 High Current
* Created By Kevin Lam, June 2, 2017
* Released for Desktop Kit
* Philip Beesley Architect Inc. / Living Architecture Systems Group
*/

#ifndef DM_HIGH_CURRENT_H_
#define DM_HIGH_CURRENT_H_

#include "Arduino.h"

class DeviceModuleHigh
{
public:
	DeviceModuleHigh(const int digital_pin_array[], const int analog_pin_array[]);

	//Arduino Functions, Accounting for Pin Mapping
	void digitalWriteDM(char port_char, int port_state);
	void analogWriteDM(char port_char, int port_state);
	int analogReadDM(char port_char);


private:
	int digital_port_pin[8];
	int analog_port_pin[8];
};


#endif //DM_HIGH_CURRENT_H_
