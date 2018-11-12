#include "../include/room.h"
#include <cstdlib>
#include <algorithm>

namespace Steinberg {
	namespace HelloWorld {
		Room::Room(float size, float decay, int sampleRate) : _audioBuffer(sampleRate * 0.5) {
			static const float earlyReflections[10] = { 0.0, 0.05, 0.07, 0.09, 0.17, 0.25, 0.43, 0.6, 0.75, 0.95 };

			_size = std::max<float>(size, 0.01);
			_sampleRate = sampleRate;
			_audioBuffer.fillWithSilence();
			_reflections = new Reflection*[10];

			int earlyReflecionsStartSample = (int) (sampleRate * _size * 0.040);
			int earlyReflecionsDurationSamples = (int) (sampleRate * _size * 0.080);
			int lateReflectionsDurationSamples = 0.5 * sampleRate - (earlyReflecionsStartSample + earlyReflecionsDurationSamples);
			
			for (int i = 0; i < 10; i++) {
				int reflectionSampleOffset = earlyReflecionsStartSample + (earlyReflecionsDurationSamples * earlyReflections[i]);
				float reflectionDecay = (1 - (reflectionSampleOffset / ((float) sampleRate * 0.5))) /* * decay*/;
				_reflections[i] = new Reflection(&_audioBuffer, reflectionSampleOffset, reflectionDecay);
			}
		}

		Room::~Room() {
			for (int i = 0; i < 10; i++) {
				delete _reflections[i];
			}
			delete[] _reflections;
		}

		void Room::pushSample(float sample) {
			_audioBuffer.push(sample);
		}

		float Room::listenSample() {
			float result = 0;
			for (int i = 0; i < 10; i++) {
				result += _reflections[i]->listen();
			}
			return result;
		}
	}
}