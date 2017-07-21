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

USBSerialComm ser;

void setup() {

  ser.Init(9600);

}


void loop() {

  ser.CheckMessage();

}
