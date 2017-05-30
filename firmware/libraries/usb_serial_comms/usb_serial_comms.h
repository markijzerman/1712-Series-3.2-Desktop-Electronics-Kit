#ifndef USB_SERIAL_COMMS_H_
#define USB_SERIAL_COMMS_H_


class USBSerialComms{

	public:
		USBSerialComms();
		~USBSerialComms();

		void SendMessage(byte msg);
		byte CheckMessage(int modifier);

};

#endif //USB_SERIAL_COMMS_H_
