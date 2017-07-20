/*
* usb_serial_comm.cpp - Library for Communication Protocol between Raspberry Pi and Node
* Created By Adam Francey, Kevin Lam, July 5, 2017
* Released for Desktop Kit
* Philip Beesley Architect Inc. / Living Architecture Systems Group
*/

#include <Arduino.h>
#include <stdint.h>
#include "usb_serial_comm.h"
#include "config.h"

USBSerialComm::USBSerialComm(){}

USBSerialComm::~USBSerialComm(){}

void USBSerialComm::SendMessage(uint8_t msg){}

bool USBSerialComm::CheckMessage(){

	message_waiting = 0;

	// Teensy ID
	uint8_t t1;
	uint8_t t2;
	uint8_t t3;

	// modifiers
	uint8_t length;
	uint8_t code;

	if (Serial.available()>=MIN_DATA_LENGTH){ // 11 = minimum message length

		// check for SOM
		for (int s = 0; s < NUM_SOM; s++){
			if (Serial.read() != SOM[s]){return 0;} // Fail: no SOM
		}

		// read Teensy ID, length, coded
		t1 = Serial.read();
		t2 = Serial.read();
		t3 = Serial.read();
		length = Serial.read();
		code = Serial.read();

		// we have already recieved 8 bytes
		int num_bytes_to_receive = (int)length - 8;
		int data_length = num_bytes_to_receive - sizeof(EOM);
		uint8_t data[data_length];

		if (Serial.available() >= num_bytes_to_receive){

			for (int i = 0; i < data_length; i++){
				data[i] = Serial.read();
			}

			// check for EOM
			for (int e = 0; e < NUM_EOM; e++){
				if (Serial.read() != EOM[e]){return 0;} // Fail: no EOM
			}

			// Success: EOM found
			last_data_length = data_length;
			last_code_received = code;
			for (int i = 0; i < data_length; i++){
				last_data_received[i] = data[i];
			}
			message_waiting = 1;
			return 1;

		} else {
			//Fail: not enough bytes
			return 0;
		}



	} else {
		// Fail: not enough bytes
		return 0;
	}
}

bool USBSerialComm::HandleMessage(uint8_t code){
	if (message_waiting){
		if (last_code_received == INSTRUCT_CODE_LED_FADE_ANIMATION){

		} else if (last_code_received == CODE_SET_ALL_IR){

		} else {
			//Fail: code not recognized
			return 0;
		}

		// Success: message handled
		message_waiting = 1;
		return 1;

	}
	else {
		//Fail: no message to be processed
		return 0;
	}
}
