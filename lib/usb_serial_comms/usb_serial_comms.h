#ifndef USB_SERIAL_COMMS_H_
#define USB_SERIAL_COMMS_H_

// delimiters
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
#define MAX_DATA_LENGTH

// message codes
#define CODE_GET_ALL_IR 0x01

class USBSerialComms{

	public:
		USBSerialComms();
		~USBSerialComms();

		void SendMessage(byte msg);
		bool CheckMessage();

		bool HandleMessage(byte code);
		// Handlers
		void GetAllIr();
		void SetAllIr();


		byte last_data_received_[MAX_DATA_LENGTH];
		int last_data_length;
		byte last_code_received;
		bool message_waiting = 0; // whether or not a received message needs to be processed

		byte SOM[3] = {SOM1,SOM2,SOM3};
		byte EOM[3] = {EOM1,EOM2,EOM3};

};

#endif //USB_SERIAL_COMMS_H_
