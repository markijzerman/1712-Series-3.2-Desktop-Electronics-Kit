#include "wav_trigger.h"
// #include "pindefs.h"
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
// #include "Toolbox.h"

// Toolbox wavtools = Toolbox();
//
// WAVTrigger::WAVTrigger(){
//   }
//
//
// WAVTrigger::~WAVTrigger(){
//     //wavtools.flashLed(13,30,20);
// }
//
// // play a track
// // trk: track number
// // code: arguments like TRK_PLAY_POLY as defined in pindefs.h
// void WAVTrigger::trackControl(int trk, int code){
//   buffer[0] = SOM1;
//   buffer[1] = SOM2;
//   buffer[2] = 0x08;
//   buffer[3] = CMD_TRACK_CONTROL;
//   buffer[4] = (uint8_t)code;
//   buffer[5] = (uint8_t)trk;
//   buffer[6] = (uint8_t)(trk>>8);
//   buffer[7] = EOM;
//
//   buffer_size = kTrackControlBufferSize;
//   //Serial.print("play sound track: ");
//   //Serial.println(trk);
//
//
// }
//
// // sets the volume of the track
// // TO DO: find bounds of gain
// // may be -10 to 10
// void WAVTrigger::masterGain(int gain) {
//
//   unsigned short vol;
//
//   buffer[0] = SOM1;
//   buffer[1] = SOM2;
//   buffer[2] = 0x07;
//   buffer[3] = CMD_MASTER_VOLUME;
//   vol = (unsigned short)gain;
//   buffer[4] = (uint8_t)vol;
//   buffer[5] = (uint8_t)(vol >> 8);
//   buffer[6] = EOM;
//
//   buffer_size = kMasterGainBufferSize;
// }
//
// void WAVTrigger::trackGain(int trk, int gain) {
//
//   unsigned short vol;
//
//   buffer[0] = SOM1;
//   buffer[1] = SOM2;
//   buffer[2] = 0x09;
//   buffer[3] = CMD_TRACK_VOLUME;
//   buffer[4] = (uint8_t)trk;
//   buffer[5] = (uint8_t)(trk >> 8);
//   vol = (unsigned short)gain;
//   buffer[6] = (uint8_t)vol;
//   buffer[7] = (uint8_t)(vol >> 8);
//   buffer[8] = EOM;
//
//   buffer_size = kTrackGainBufferSize;
// }
//
// void WAVTrigger::trackFade(int trk, int gain, int time, bool stopFlag) {
//
//   unsigned short vol;
//
//   buffer[0] = SOM1;
//   buffer[1] = SOM2;
//   buffer[2] = 0x0c;
//   buffer[3] = CMD_TRACK_FADE;
//   buffer[4] = (uint8_t)trk;
//   buffer[5] = (uint8_t)(trk >> 8);
//   vol = (unsigned short)gain;
//   buffer[6] = (uint8_t)vol;
//   buffer[7] = (uint8_t)(vol >> 8);
//   buffer[8] = (uint8_t)time;
//   buffer[9] = (uint8_t)(time >> 8);
//   buffer[10] = stopFlag;
//   buffer[11] = EOM;
//
//   buffer_size = kFadeBufferSize;
// }
