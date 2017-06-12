/*
* dm_low_current.c[[ - Library for Device Module 3.1 Low Current
* Created By Kevin Lam, June 5, 2017
* Released for Desktop Kit
* Philip Beesley Architect Inc. / Living Architecture Systems Group
*/

#pragma once
#include "dm_low_current.h"

DeviceModuleLow::DeviceModuleLow() {

}

void DeviceModuleLow::writeActuator(char port_char, bool port_state){
	
}

int DeviceModuleLow::analogRead(char port_char){

	int pin_number = 0;

	if (port_char == 'C') { pin_number = analog_port_pin[5]; }
	else if (port_char == 'D') { pin_number = analog_port_pin[4]; }

	return analogRead(pin_number);
}

void DeviceModuleLow::setPinMapping(const int digital_pin_array[], const int analog_pin_array[]){

	memcpy(digital_port_pin, digital_pin_array, sizeof(digital_port_pin));
	memcpy(analog_port_pin, analog_pin_array, sizeof(analog_port_pin));

}
