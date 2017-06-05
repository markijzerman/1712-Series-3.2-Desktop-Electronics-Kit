/*
* dm_high_current.cpp - Library for Device Module 3.1 High Current
* Created By Kevin Lam, June 5, 2017
* Released for Desktop Kit
* Philip Beesley Architect Inc. / Living Architecture Systems Group
*/

#include "dm_high_current.h"
#include "Arduino.h"

DeviceModuleHigh::DeviceModuleHigh() {

	pinMode(digital_port_pin[0], OUTPUT);
	pinMode(digital_port_pin[1], OUTPUT);
	pinMode(digital_port_pin[2], OUTPUT);
	pinMode(digital_port_pin[3], OUTPUT);
	pinMode(digital_port_pin[6], OUTPUT);
	pinMode(digital_port_pin[7], OUTPUT);

}


void DeviceModuleHigh::setPinMapping(const int digital_pin_array[], const int analog_pin_array[]){

	memcpy(digital_port_pin, digital_pin_array, sizeof(digital_port_pin));
	memcpy(analog_port_pin, analog_pin_array, sizeof(analog_port_pin));

}

void DeviceModuleHigh::writeActuator(int port_number, int port_state) {
	
	digitalWrite(digital_port_pin[port_number - 1], port_state);

}

int DeviceModuleHigh::readAnalog(int port_number){

	return analogRead(analog_port_pin[port_number - 1]);

}