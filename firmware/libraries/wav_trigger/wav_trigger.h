#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

#ifndef __WAV__
#define __WAV__

class WAVTrigger{
    public:   

        WAVTrigger();
        ~WAVTrigger();
        void trackControl(int trk, int code);
        void masterGain(int gain);
        void trackFade(int trk, int gain, int time, bool stopFlag);
        void trackGain(int trk, int gain);

        const int kMaxBufferSize = 12;
        const int kTrackControlBufferSize = 8;
        const int kMasterGainBufferSize = 7;
        const int kTrackGainBufferSize = 9;
        const int kFadeBufferSize = 12;
        int buffer_size;
        uint8_t buffer[12];
              
};

#endif
