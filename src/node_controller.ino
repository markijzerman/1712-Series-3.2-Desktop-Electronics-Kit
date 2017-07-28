/*
* node_controller.ino - Example Sketch for Serial Communication between Node and RPi/Computer
* Created By Kevin Lam, June 5, 2017
* Released for Desktop Kit
* Philip Beesley Architect Inc. / Living Architecture Systems Group
*/

//#include "node_ports.h"
#include "Arduino.h"
#include "wav_trigger.h"

// Initalize a WAV trigger attached to hardware Serial1 (or 2, 3)
WAVTrigger wav_trigger_hard(1);

// Or initialize a WAV trigger to use a software serial
// rx: pin 3
// tx: pin 4
WAVTrigger wav_trigger_soft(3,4);

void setup() {

    // begin the serial ports
    wav_trigger_hard.begin();
    wav_trigger_soft.begin();
}

void loop() {
    // play the first track every 2 seconds, alternating triggers
    delay(2000);
    wav_trigger_hard.trackControl(1,wav_trigger_hard.TRK_PLAY_POLY);
    delay(2000);
    wav_trigger_soft.trackControl(1,wav_trigger_soft.TRK_PLAY_POLY);

}
