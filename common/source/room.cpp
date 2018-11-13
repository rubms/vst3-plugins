#include "../include/room.h"
#include <cstdlib>
#include <algorithm>

namespace Steinberg {
	namespace RubenVST3 {
		Room::Room(float size, float decay, int sampleRate) {
			_size = std::max<float>(size, 0.01);
			_sampleRate = sampleRate;
			_decay = decay;

			_numBuffers = 4;
			_audioBuffers = new CircularAudioBuffer*[_numBuffers];
			float reflections[4] = { 0.002, 0.003, 0.005, 0.007 /*, 0.0101, 0.0117, 0.015, 0.019, 0.024, 0.028*/ };
			for (int i = 0; i < _numBuffers; i++) {
				_audioBuffers[i] = new CircularAudioBuffer(sampleRate * reflections[i] * _size * 10);
				_audioBuffers[i]->fillWithSilence();
			}
		}

		Room::~Room() {
			for (int i = 0; i < _numBuffers; i++) {
				delete _audioBuffers[i];
			}
			delete[] _audioBuffers;
		}

		void Room::feedWithHadamardFeedbackMatrix(float sample) {
			float feedback1 = _audioBuffers[0]->peek() + _audioBuffers[1]->peek() + _audioBuffers[2]->peek() + _audioBuffers[3]->peek();
			float feedback2 = _audioBuffers[0]->peek() - _audioBuffers[1]->peek() + _audioBuffers[2]->peek() - _audioBuffers[3]->peek();
			float feedback3 = _audioBuffers[0]->peek() + _audioBuffers[1]->peek() - _audioBuffers[2]->peek() - _audioBuffers[3]->peek();
			float feedback4 = _audioBuffers[0]->peek() - _audioBuffers[1]->peek() - _audioBuffers[2]->peek() + _audioBuffers[3]->peek();

			_audioBuffers[0]->push((sample + feedback1) * (1 - _decay));
			_audioBuffers[1]->push((sample + feedback2) * (1 - _decay));
			_audioBuffers[2]->push((sample + feedback3) * (1 - _decay));
			_audioBuffers[3]->push((sample + feedback4) * (1 - _decay));
		}

		float Room::listenSample() {
			float reflectionSum = 0;

			for (int i = 0; i < _numBuffers; i++) {
				reflectionSum += _audioBuffers[i]->peek();
			}

			return reflectionSum;
		}
	}
}