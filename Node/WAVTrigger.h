#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

#ifndef __WAV__
#define __WAV__

class WAVTrigger{
    public:   

        WAVTrigger();
        WAVTrigger(bool hard);
        WAVTrigger(int pin_softRX, int pin_softTX);
        ~WAVTrigger();

        SoftwareSerial WAVSerial = SoftwareSerial(3,4); // init with port 2 pins, just because. They get changed upon init
        bool hardSerial; // 0 = softserial, 1 = hardserial
        void WAVStart();
        void trackControl(int trk, int code);
        void masterGain(int gain);
        void trackFade(int trk, int gain, int time, bool stopFlag);
        void trackGain(int trk, int gain);

        void playInFuture(int trk, int ms);
        void updateTracks();

        // countdowns to play a future sound
        int futureCountdown[20] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
        // the track to play when the countdown above hits zero
        int futureTrack[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
              
};

#endif
