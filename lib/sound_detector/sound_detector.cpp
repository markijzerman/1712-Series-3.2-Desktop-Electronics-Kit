/*
* sound_detector.cpp - Library for Sparkfun Sound Detector and FFT
* Created By Kevin Lam, June 5, 2017
* Released for Desktop Kit
* Philip Beesley Architect Inc. / Living Architecture Systems Group
*/

#include <Arduino.h>
#include "sound_detector.h"

SoundDetector::SoundDetector(const int input_pin, const int envelope_pin) : audio_input_pin(input_pin), audio_envelope_pin(envelope_pin) {

}

int SoundDetector::readRawAudio(){
	return analogRead(audio_input_pin);
}

void SoundDetector::runFFT(){

	arm_cfft_radix4_instance_f32 fft_inst;
    arm_cfft_radix4_init_f32(&fft_inst, FFT_SIZE, 0, 1);
    arm_cfft_radix4_f32(&fft_inst, samples);
	arm_cmplx_mag_f32(samples, magnitudes, FFT_SIZE);

}

int SoundDetector::frequencyToBin(float frequency) {
  float binFrequency = float(SAMPLE_RATE_HZ) / float(FFT_SIZE);
  return int(frequency / binFrequency);
}
