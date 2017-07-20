/*
* usb_serial_comm.cpp - Library for Communication Protocol between Raspberry Pi and Node
* Created By Adam Francey, Kevin Lam, July 5, 2017
* Released for Desktop Kit
* Philip Beesley Architect Inc. / Living Architecture Systems Group
*/

#ifndef USB_SERIAL_COMM_H_
#define USB_SERIAL_COMM_H_

// Delimiters
#define SOM1 0x00
#define SOM2 0x00
#define SOM3 0x00
#define EOM1 0xff
#define EOM2 0xff
#define EOM3 0xff
#define NUM_SOM 3
#define NUM_EOM 3
#define NUM_ID 3

// message code lengths (length of data array)
// TO DO: PUT INTO CONFIG CONSTANTS
#define MIN_DATA_LENGTH 11
#define MAX_DATA_LENGTH 255

// message codes
// TO DO: PUT INTO CONFIG CONSTANTS
#define CODE_GET_ALL_IR 0x01
#define CODE_SET_ALL_IR 0x02

class USBSerialComm{

	public:
		USBSerialComm();
		~USBSerialComm();

		void Init();

		void SendMessage(uint8_t msg);
		bool CheckMessage();

		bool HandleMessage();
		// Handlers

		uint8_t last_data_received_[MAX_DATA_LENGTH] = { 0 };
		int last_data_length_;
		uint8_t last_code_received_;
		bool message_waiting_ = 0; // whether or not a received message needs to be processed

		uint8_t SOM[3] = {SOM1,SOM2,SOM3};
		uint8_t EOM[3] = {EOM1,EOM2,EOM3};

};

#endif //USB_SERIAL_COMMS_H_
