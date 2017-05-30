#ifndef SOUND_DETECTOR_H_
#define SOUND_DETECTOR_H_


class SoundDetector{

	public:
		SoundDetector();
		~SoundDetector();

		int ReadRawAudio();
		int ReadEnvelope();

		int audio_pin_;
		int envelope_pin_;

};

#endif //SOUND_DETECTOR_H_