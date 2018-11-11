#include "../include/spring.h"

namespace Steinberg {
	namespace HelloWorld {
		Spring::Spring(int loops, float springDelaySeconds, float decay, int sampleRate) {
			_numberOfLoops = loops;
			_decay = decay;

			if (_numberOfLoops > 0) {
				_audioBuffers = new CircularAudioBuffer*[_numberOfLoops * 2];
				for (int i = 0; i < _numberOfLoops * 2; i++) {
					int springDelaySamples = sampleRate * springDelaySeconds;
					_audioBuffers[i] = new CircularAudioBuffer(springDelaySamples);
					_audioBuffers[i]->fillWithSilence();
				}
			}
			else {
				_audioBuffers = nullptr;
			}
		}

		Spring::~Spring() {
			if (_numberOfLoops > 0) {
				for (int i = 0; i < _numberOfLoops * 2; i++) {
					delete _audioBuffers[i];
				}
				delete[] _audioBuffers;
			}
		}

		void Spring::push(float sample) {
			if (_numberOfLoops > 0) {
				_audioBuffers[0]->push(sample * (1 - _decay));
				for (int i = 1; i < _numberOfLoops * 2; i++) {
					_audioBuffers[i]->push(
						(i % 2 == 0) ? sample * (1 - _decay) : 0
						+ _audioBuffers[i - 1]->peek() * (1 - _decay));
				}
			}
		}

		float Spring::peek() {
			float result = 0;
			for (int i = 0; i < _numberOfLoops * 2; i++) {
				result += (i % 2 == 0) ? _audioBuffers[i]->peek() : 0;
			}
			return result;
		}
	}
}