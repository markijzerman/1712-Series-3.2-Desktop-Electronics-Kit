#ifndef XBEE_SERIAL_COMMS_H_
#define XBEE_SERIAL_COMMS_H_


class XBSerialComms{

	public:
		XBSerialComms();
		~XBSerialComms();

		void SendMessage(byte msg);
		byte CheckMessage(int modifier);

};

#endif //XBEE_SERIAL_COMMS_H_