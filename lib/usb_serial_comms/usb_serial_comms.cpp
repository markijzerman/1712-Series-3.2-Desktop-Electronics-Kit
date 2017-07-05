#include usb_serial_comms.h

USBSerialComms::USBSerialComms(){}
USBSerialComms::~USBSerialComms(){}

void USBSerialComms::SendMessage(){}

// checks for incoming serial message
// return reception status
// Updates following USBSerialComms class members:
// message_waiting
// last_data_received
// last_code_received
// last_data_length
bool USBSerialComms::CheckMessage(){

	message_waiting = 0;

	// Teensy ID
	byte t1;
	byte t2;
	byte t3;

	// modifiers
	byte length;
	byte code;

	if (Serial.available()>=11){ // 11 = minimum message length

		// check for SOM
		for (int s = 0; s < NUM_SOM; s++){
			if (Serial.read() != SOM[s]){return 0;} // Fail: no SOM
		}

		// read Teensy ID, length, code
		t1 = Serial.read();
		t2 = Serial.read();
		t3 = Serial.read();
		length = Serial.read();
		code = Serial.read();

		// we have already recieved 8 bytes
		int num_bytes_to_receive = length - 8;
		int data_length = num_bytes_to_receive - EOM;
		byte data[data_length];

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
		return 0
	}
}

void HandleMessage(){
	if (message_waiting){
		if (last_code_received == CODE_GET_ALL_IR){
			GetAllIr();
		} else if (last_code_received == CODE_SET_ALL_IR){
			SetAllIr();
		} else {
			//Fail: code not recognized
			return 0;
		}

		// Success: message handled
		message_waiting = 
		return 1;

	} else {
		//Fail: no message to be processed
		return 0;
	}
}

void GetAllIr(){

}

void SetAllIr(){

}