/*
* node_ports.h - Library for Device Module 3.2 High Current
* Created By Kevin Lam, June 2, 2017
* Released for Desktop Kit
* Philip Beesley Architect Inc. / Living Architecture Systems Group
*/

#ifndef NODE_PORTS_h
#define NODE_PORTS_h

#include "Arduino.h"
#include "dm_high_current.h"
//#include "dm_low_current.h"

class Port0
{
public:
	Port0();
	Port0(String board_type);
	//JackPlateBoard JackPlate;
	DeviceModuleHigh DMHigh;
	//DeviceModuleLow DMLow;
private:
	const int kDigitalPortPin[8] = { 3, 4, 5, 20, 27, A11, 16, 17 };
	const int kAnalogPortPin[8] = { 3, 4, 5, A6, A16, A11, A2, A3 };
};

class Port1
{
public:
	Port1();
	Port1(String board_type);
	//JackPlateBoard JackPlate;
	DeviceModuleHigh DMHigh;
	//DeviceModuleLow DMLow; 
private:
	const int kDigitalPortPin[8] = { 25, 32, 6, 21, 28, A13, 26, 31 };
	const int kAnalogPortPin[8] = { 25, 32, 6, A7, A17, A13, A15, A20 };
};

class Port2
{
public:
	Port2();
	Port2(String board_type);
	//JackPlateBoard JackPlate;
	DeviceModuleHigh DMHigh;
	//DeviceModuleLow DMLow;
private:
	const int kDigitalPortPin[8] = { 9, 10, 22, 23, 14, 15, 29, 30 };
	const int kAnalogPortPin[8] = { 9, 10, A8, A9, A0, A1, A18, A19 };
};

class PortS
{
private:
	const int kDigitalPortPin[8] = { 7, 8, 33, 11, 12, 13, 18, 19 };
	const int kAnalogPortPin[8] = { 7, 8, 33, 11, 12, 13, A4, A5 };
public:
	PortS();
	PortS(String board_type);
	//JackPlateBoard JackPlate;
	DeviceModuleHigh DMHigh;
	//DeviceModuleLow DMLow;
};

#endif