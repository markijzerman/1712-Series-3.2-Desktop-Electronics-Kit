/*
* node_controller.ino - Example Sketch for Serial Communication between Node and RPi/Computer
* Created By Kevin Lam, June 5, 2017
* Released for Desktop Kit
* Philip Beesley Architect Inc. / Living Architecture Systems Group
*/

#include "config.h"
#include "dm_high_current.h"
#include "dm_low_current.h"
#include "node_ports.h"
#include "Arduino.h"
#include "wav_trigger.h"
#include "sound_detector.h"
#include "usb_serial_comm.h"

// Port2 port2(kPort2BoardType);
//
// SoftwareSerial WAVTriggerSerial(3,4); // serial pins connected to P0;
// wav_trigger WAVTrigger;

void setup() {

  // pinMode(9, OUTPUT);
	// Serial.begin(kBaudRate);
  //
  // WAVTrigger.begin(57600);

  pinMode(13, OUTPUT);

}

void loop() {

  digitalWrite(13, HIGH);

// 	if (Serial.available())	{
// //		String input_string = "";
//     int input_integer;
// 		while (Serial.available()){
// //			char input_char = Serial.read();
// //			input_string += input_char;
//       input_integer = Serial.read();
// 		}
// 		if (input_integer) {
//       Serial.print("Input Integer: ");
//       Serial.println(input_integer);
// 			port2.DMHigh.writeActuator(kActuatorPort, 1);
// 			delay(1000);
// 			port2.DMHigh.writeActuator(kActuatorPort, 0);
// 			delay(1000);
// 		}
// 	}
// 	if (port2.DMHigh.readAnalog(kSensorPort) > 300) {
// 		Serial.println(port2.DMHigh.readAnalog(kSensorPort));
// 	}
//
//
//  //play a sound
//  WAVTrigger.trackControl(1, TRK_PLAY_POLY)
//  WAVTriggerSerial.write(WAVTrigger.buffer,WAVTrigger.buffer_size)
//
//
//   delay(500);

}
