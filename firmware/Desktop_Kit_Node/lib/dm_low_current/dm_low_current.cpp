/*
* dm_low_current.cpp - Library for Device Module 3.1 Low Current
* Created By Kevin Lam, June 5, 2017
* Released for Desktop Kit
* Philip Beesley Architect Inc. / Living Architecture Systems Group
*/

#include "dm_low_current.h"

DeviceModuleLow::DeviceModuleLow(const int digital_pin_array[], const int analog_pin_array[]):
	NeoPixelD(NUM_PIXELS_D, digital_port_pin[4], NEO_GRBW + NEO_KHZ800),
	NeoPixelE(NUM_PIXELS_E, digital_port_pin[3], NEO_GRBW + NEO_KHZ800),
	NeoPixelF(NUM_PIXELS_F, digital_port_pin[2], NEO_GRBW + NEO_KHZ800) {

	memcpy(digital_port_pin, digital_pin_array, sizeof(digital_port_pin));
	memcpy(analog_port_pin, analog_pin_array, sizeof(analog_port_pin));

	pinMode(digital_port_pin[0], OUTPUT);
	pinMode(digital_port_pin[1], OUTPUT);
	pinMode(digital_port_pin[2], OUTPUT);
	pinMode(digital_port_pin[3], OUTPUT);
	pinMode(digital_port_pin[6], OUTPUT);
	pinMode(digital_port_pin[7], OUTPUT);
	pinMode(digital_port_pin[4], INPUT);
	pinMode(digital_port_pin[5], INPUT);

}


void DeviceModuleLow::digitalWriteDM(char port_char, bool port_state){

}

int DeviceModuleLow::analogReadDM(char port_char){

	int pin_number = 0;

	if (port_char == 'C') { pin_number = analog_port_pin[5]; }
	else if (port_char == 'D') { pin_number = analog_port_pin[4]; }

	return analogRead(pin_number);
}
