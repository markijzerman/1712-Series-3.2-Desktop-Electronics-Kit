/*
* sound_detector.h - Library for Sparkfun Sound Detector and FFT
* Created By Kevin Lam, June 5, 2017
* Released for Desktop Kit
* Philip Beesley Architect Inc. / Living Architecture Systems Group
*/

#ifndef SOUND_DETECTOR_H_
#define SOUND_DETECTOR_H_

#include <arm_math.h>
#include <IntervalTimer.h>

#define FFT_SIZE 256

class SoundDetector{

	public:
		SoundDetector(const int input_pin, const int envelope_pin);
		~SoundDetector();

		int readRawAudio();
		int readEnvelope();
		void runFFT();

		void beginSampling();
		bool isSamplingDone();



	private:

		int audio_input_pin;
		int audio_envelope_pin;

		const int SAMPLE_RATE_HZ = 9000;		// Frequency between sampling each value in the input. For given sample rate, frequencies up to half the rate can be measured.
		const int ANALOG_READ_RESOLUTION = 10; 	// Bits of resolution for the ADC.
		const int ANALOG_READ_AVERAGING = 16;  	// Number of samples to average with each ADC reading.

		IntervalTimer samplingTimer;
		float samples[FFT_SIZE*2];
		float magnitudes[FFT_SIZE];
		int sampleCounter = 0;
		float frequencyWindow[2];

		void windowMean(float* magnitudes, int lowBin, int highBin, float* windowMean, float* otherMean);
		int frequencyToBin(float frequency);
		void samplingCallback();

};

#endif //SOUND_DETECTOR_H_
