/*
* node_ports.cpp - Library for Device Module 3.2 High Current
* Created By Kevin Lam, June 5, 2017
* Released for Desktop Kit
* Philip Beesley Architect Inc. / Living Architecture Systems Group
*/

#include "node_ports.h"

Port0::Port0() {

}

Port0::Port0(String board_type){

	if (board_type == "DM_HIGH") {
		DMHigh.setPinMapping((*this).kDigitalPortPin, (*this).kAnalogPortPin);
	}
	else if (board_type == "DM_LOW") {
		DMLow.setPinMapping((*this).kDigitalPortPin, (*this).kAnalogPortPin);
	}

}

Port1::Port1() {



}

Port2::Port2() {

}

Port2::Port2(String board_type) {

	if (board_type == "2") {
		DMHigh.setPinMapping((*this).kDigitalPortPin, (*this).kAnalogPortPin);
	}

}

PortS::PortS() {

}