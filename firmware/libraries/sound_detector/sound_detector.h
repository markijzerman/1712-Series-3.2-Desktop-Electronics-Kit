/*
* sound_detector.h - Library for Sparkfun Sound Detector and FFT
* Created By Kevin Lam, June 5, 2017
* Released for Desktop Kit
* Philip Beesley Architect Inc. / Living Architecture Systems Group
*/

#ifndef SOUND_DETECTOR_H_
#define SOUND_DETECTOR_H_

#include <arm_math.h>

class SoundDetector{

	public:
		SoundDetector();
		~SoundDetector();

		int readRawAudio();
		int readEnvelope();
		void runFFT();
		void 

		void beginSampling();
		bool isSamplingDone();



	private:

		int audio_input_pin_;
		int envelope_pin;

		const int SAMPLE_RATE_HZ = 9000;		// Frequency between sampling each value in the input. For given sample rate, frequencies up to half the rate can be measured.
		const int FFT_SIZE = 256;              	// Size of the FFT, number of output frequency bins.  At most, 256 for Teensy 3.0
		const int ANALOG_READ_RESOLUTION = 10; 	// Bits of resolution for the ADC.
		const int ANALOG_READ_AVERAGING = 16;  	// Number of samples to average with each ADC reading.

		IntervalTimer samplingTimer;
		float samples[FFT_SIZE*2];
		float magnitudes[FFT_SIZE];
		int sampleCounter = 0;
		float frequencyWindow[NEO_PIXEL_COUNT+1];

		void windowMean(float* magnitudes, int lowBin, int highBin, float* windowMean, float* otherMean);
		void frequencyToBin(float frequency);
		void samplingCallback();

};

#endif //SOUND_DETECTOR_H_