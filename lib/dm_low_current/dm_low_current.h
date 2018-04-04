/*
* dm_low_current.h - Library for Device Module 3.1 Low Current
* Created By Kevin Lam, June 5, 2017
* Released for Desktop Kit
* Philip Beesley Architect Inc. / Living Architecture Systems Group
*/

#ifndef DM_LOW_CURRENT_H_
#define DM_LOW_CURRENT_H_

#include "Arduino.h"
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

class DeviceModuleLow
{
public:
	DeviceModuleLow(const int digital_pin_array[], const int analog_pin_array[]);

	//Arduino Functions, Accounting for Pin Mapping
	void digitalWriteDM(char port_char, bool port_state);
	void analogWriteDM(char port_char, bool port_state);
	int analogReadDM(char port_char);

	//Neopixel
	Adafruit_NeoPixel NeoPixelD;
	Adafruit_NeoPixel NeoPixelE;
	Adafruit_NeoPixel NeoPixelF;

	//Sound Detector

private:
	int digital_port_pin[8];
	int analog_port_pin[8];

	const int NUM_PIXELS_D = 1;
	const int NUM_PIXELS_E = 1;
	const int NUM_PIXELS_F = 1;

};


#endif //DM_LOW_CURRENT_H_
