/*
* usb_serial_comm.cpp - Library for Communication Protocol between Raspberry Pi and Node
* Created By Adam Francey, Kevin Lam, July 5, 2017
* Released for Desktop Kit
* Philip Beesley Architect Inc. / Living Architecture Systems Group
* 
* Message Format (see related doc [WIP] for details)
* where <value> is the value represented as a byte:
* <SOM1><SOM2><SOM3><TeensyId1><TeensyId2><TeensyId3><total number of bytes in message><code><data1>...<dataN><EOM1><EOM2><EOM3>
*/

#include <Arduino.h>
#include <stdint.h>
#include "usb_serial_comm.h"
#include "config.h"

USBSerialComm::USBSerialComm(){}

USBSerialComm::~USBSerialComm(){}

void USBSerialComm::Init(int baud){

	// USBSerialComm always uses dedicated USB serial
	Serial.begin(baud);

}

void USBSerialComm::SendMessage(uint8_t code){
	// Send SOM
	for (int i = 0; i < NUM_SOM; i++){
		Serial.write(SOM[i]);
	}

	// Send TeensyID
	for (int i = 0; i < NUM_ID; i++){
		Serial.write(ID[i]);
	}

	// Send message length
	//        				 SOM       ID       length   code  EOM
	uint8_t message_length = NUM_SOM + NUM_ID + 1      + 1   + NUM_EOM;
	Serial.write(message_length);

	// Send code
	Serial.write(code);


	// Send EOM
	for (int i = 0; i < NUM_EOM; i++){
		Serial.write(EOM[i]);
	}	

}

void USBSerialComm::SendMessage(uint8_t code, uint8_t data[]){

	uint8_t data_length = sizeof(data); // = # of elements in data since each element = 1 byte

	// Send SOM
	for (int i = 0; i < NUM_SOM; i++){
		Serial.write(SOM[i]);
	}

	// Send TeensyID
	for (int i = 0; i < NUM_ID; i++){
		Serial.write(ID[i]);
	}

	// Send message length
	//        				 SOM       ID       length   code   data          EOM
	uint8_t message_length = NUM_SOM + NUM_ID + 1      + 1    + data_length + NUM_EOM;
	Serial.write(message_length);

	// Send code
	Serial.write(code);
	// Send data
	for (int i = 0; i < data_length; i++){
		Serial.write(data[i]);
	}

	// Send EOM
	for (int i = 0; i < NUM_EOM; i++){
		Serial.write(EOM[i]);
	}	


}


// CheckMessage
// Reads the serial port for an incoming sequence of bytes
// if sequence follows requirements of a message defined in docs, returns 1 and
// updates the following USBSerialComm members:
// last_data_length, last_code_received, last_data_received, message_waiting
// if requirements fail, returns 0
bool USBSerialComm::CheckMessage(){

	message_waiting_ = 0;

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
		int data_length = num_bytes_to_receive - NUM_EOM;
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
			last_data_length_ = data_length;
			last_code_received_ = code;
			for (int i = 0; i < data_length; i++){
				last_data_received_[i] = data[i];
			}
			message_waiting_ = 1;
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

bool USBSerialComm::HandleMessage(){
	if (message_waiting_){

		if (last_code_received_ == INSTRUCT_CODE_TEST_COMMUNICATION){

			SendMessage(INSTRUCT_CODE_TEST_COMMUNICATION);

		} else if (last_code_received_ == INSTRUCT_CODE_TEST_LED){

			//do something

		} else if (last_code_received_ == INSTRUCT_CODE_LED_FADE_ANIMATION){

			uint8_t channel = last_data_received_[0];
			uint8_t fade_increment = last_data_received_[1];
			uint8_t wait_time_hi = last_data_received_[2];
			uint8_t wait_time_lo = last_data_received_[3];

			uint16_t wait_time = wait_time_hi << 8 | wait_time_lo;

		} else {
			//Fail: code not recognized
			return 0;
		}

		// Success: message handled
		message_waiting_ = 0;
		return 1;

	}
	else {
		//Fail: no message to be processed
		return 0;
	}
}
