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

	if (board_type == "1") {
		DMHigh.setPinMapping((*this).kDigitalPortPin, (*this).kAnalogPortPin);
	}

}

Port2::Port2(String board_type) {

	if (board_type == "1") {
		DMHigh.setPinMapping((*this).kDigitalPortPin, (*this).kAnalogPortPin);
	}

}