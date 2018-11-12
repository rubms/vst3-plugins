#include "../include/room.h"
#include <cstdlib>
#include <algorithm>

namespace Steinberg {
	namespace HelloWorld {
		Room::Room(float size, float decay, int sampleRate) {

			_size = std::max<float>(size, 0.01);
			_sampleRate = sampleRate;
			_decay = decay;
			_audioBuffers = new CircularAudioBuffer*[6];

			_audioBuffers[0] = new CircularAudioBuffer(sampleRate * 0.0101);
			_audioBuffers[1] = new CircularAudioBuffer(sampleRate * 0.0117);
			_audioBuffers[2] = new CircularAudioBuffer(sampleRate * 0.015);
			_audioBuffers[3] = new CircularAudioBuffer(sampleRate * 0.019);
			_audioBuffers[4] = new CircularAudioBuffer(sampleRate * 0.021);
			_audioBuffers[5] = new CircularAudioBuffer(sampleRate * 0.023);
		}

		Room::~Room() {
			for (int i = 0; i < 6; i++) {
				delete _audioBuffers[i];
			}
			delete[] _audioBuffers;
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