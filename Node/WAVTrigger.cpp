#include "WAVTrigger.h"
#include "pindefs.h"
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#include "Toolbox.h"

Toolbox wavtools = Toolbox();

WAVTrigger::WAVTrigger(){
  }

// NOTE!! Hardware serial ports on p2 (pins 9, 10) don't play nice with redefinition here
// must use alternatate constructor below for port 2
WAVTrigger::WAVTrigger(int pin_softRX, int pin_softTX): WAVSerial(SoftwareSerial(pin_softRX,pin_softTX)){
  
  //WAVSerial = SoftwareSerial(3, 4); // this did not work! must put it above - TO DO: find out why!

  // we are using software serial
  hardSerial = false;
}

// constructor for port 2
WAVTrigger::WAVTrigger(bool hard){

  // using hardware serial port
  hardSerial = true;
}


WAVTrigger::~WAVTrigger(){
    //wavtools.flashLed(13,30,20);
}

// starts the serial port for the WAV trigger
void WAVTrigger::WAVStart(void){
  uint8_t txbuf[5];

  if (hardSerial){
    Serial2.begin(57600);
  } else {
    WAVSerial.begin(57600);
  }


  // request version string
  txbuf[0] = SOM1;
  txbuf[1] = SOM2;
  txbuf[2] = 0x05;
  txbuf[3] = CMD_GET_VERSION;
  txbuf[4] = EOM;

  if (hardSerial){
    Serial2.write(txbuf,5);
  } else {
    WAVSerial.write(txbuf,5);
  }

  // request system info
  txbuf[0] = SOM1;
  txbuf[1] = SOM2;
  txbuf[2] = 0x05;
  txbuf[3] = CMD_GET_SYS_INFO;
  txbuf[4] = EOM;

  if (hardSerial){
    Serial2.write(txbuf,5);
  } else {
    WAVSerial.write(txbuf,5);
  }
  
}

// play a track
// trk: track number
// code: arguments like TRK_PLAY_POLY as defined in pindefs.h
void WAVTrigger::trackControl(int trk, int code){
  uint8_t txbuf[8];
  txbuf[0] = SOM1;
  txbuf[1] = SOM2;
  txbuf[2] = 0x08;
  txbuf[3] = CMD_TRACK_CONTROL;
  txbuf[4] = (uint8_t)code;
  txbuf[5] = (uint8_t)trk;
  txbuf[6] = (uint8_t)(trk>>8);
  txbuf[7] = EOM;

  if (hardSerial){
    Serial2.write(txbuf,8);
  } else {
    WAVSerial.write(txbuf,8);
  }

  //Serial.print("play sound track: ");
  //Serial.println(trk);


}

// sets the volume of the track
// TO DO: find bounds of gain
// may be -10 to 10
void WAVTrigger::masterGain(int gain) {

  uint8_t txbuf[7];
  unsigned short vol;

  txbuf[0] = SOM1;
  txbuf[1] = SOM2;
  txbuf[2] = 0x07;
  txbuf[3] = CMD_MASTER_VOLUME;
  vol = (unsigned short)gain;
  txbuf[4] = (uint8_t)vol;
  txbuf[5] = (uint8_t)(vol >> 8);
  txbuf[6] = EOM;
  
  if (hardSerial){
    Serial2.write(txbuf,7);
  } else {
    WAVSerial.write(txbuf,7);
  }
}

void WAVTrigger::trackGain(int trk, int gain) {

  uint8_t txbuf[9];
  unsigned short vol;

  txbuf[0] = SOM1;
  txbuf[1] = SOM2;
  txbuf[2] = 0x09;
  txbuf[3] = CMD_TRACK_VOLUME;
  txbuf[4] = (uint8_t)trk;
  txbuf[5] = (uint8_t)(trk >> 8);
  vol = (unsigned short)gain;
  txbuf[6] = (uint8_t)vol;
  txbuf[7] = (uint8_t)(vol >> 8);
  txbuf[8] = EOM;
  
  if (hardSerial)
    Serial2.write(txbuf,9);
  else
    WAVSerial.write(txbuf,9);
}

void WAVTrigger::trackFade(int trk, int gain, int time, bool stopFlag) {

uint8_t txbuf[12];
unsigned short vol;

  txbuf[0] = SOM1;
  txbuf[1] = SOM2;
  txbuf[2] = 0x0c;
  txbuf[3] = CMD_TRACK_FADE;
  txbuf[4] = (uint8_t)trk;
  txbuf[5] = (uint8_t)(trk >> 8);
  vol = (unsigned short)gain;
  txbuf[6] = (uint8_t)vol;
  txbuf[7] = (uint8_t)(vol >> 8);
  txbuf[8] = (uint8_t)time;
  txbuf[9] = (uint8_t)(time >> 8);
  txbuf[10] = stopFlag;
  txbuf[11] = EOM;

  if (hardSerial)
    Serial2.write(txbuf, 12);
  else
    WAVSerial.write(txbuf, 12);
}

// registers a track to be played in the future
// trk: track number
// ms: milliseconds to wait
void WAVTrigger::playInFuture(int trk, int ms){
  
  // each frame is FRAMERATE ms
  int framesToWait = ms/FRAMERATE;

  int foundOpenSlot = false;
  int slot = 0;
  while (foundOpenSlot == false && slot < 20){

      // -1 designates the slot is open
      if (futureCountdown[slot] == -1){
        futureCountdown[slot] = framesToWait;
        futureTrack[slot] = trk;
        foundOpenSlot = true;
      }
      
      slot = slot + 1;
    }

 //either a track is posted to the future, or nothing happens

  }

// checks if a track is to be played
void WAVTrigger::updateTracks(){
  for (int slot = 0; slot < 20; slot++){
    if (futureCountdown[slot] == 0){
      // if the countdown has hit the bottom, play the track and empty the slot
      trackGain(futureTrack[slot], -70);
      trackControl(futureTrack[slot], TRK_PLAY_POLY);
      trackFade(futureTrack[slot], 0, rampUpTime, 0);
      futureCountdown[slot] = -1;
    } else if (futureCountdown[slot] > 0) {
      // this track is still waiting to be played, decrement the counter
      futureCountdown[slot] = futureCountdown[slot] - 1;
    }

  // else futureCountdown[slot] = -1, so don't do anything  
  }
}


