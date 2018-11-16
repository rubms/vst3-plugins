#include "../include/room.h"
#include <cstdlib>
#include <algorithm>
#include <cmath>

namespace Steinberg {
	namespace RubenVST3 {
		Room::Room(int sampleRate,
				float damping,
				float roomSize,
				float reverbTime,
				float earlyReflectionsLevel,
				float tailReflectionsLevel,
				float inputBandWith) : _inputDamper(1.0 - inputBandWith) {
			
			_sampleRate = sampleRate;
			_damping = damping;
			_roomSize = roomSize;
			_reverbTime = reverbTime;
			_earlyReflectionsLevel = earlyReflectionsLevel;
			_tailReflectionsLevel = tailReflectionsLevel;
			_inputBandWith = inputBandWith;

			_largestDelay = _sampleRate * _roomSize / SPEED_OF_SOUND;

			_fixedDelays = new FDNDelay*[NUMBER_OF_FDN_DELAYS];
			_fixedDelays[0] = new FDNDelay((int)round(1.000000 * _largestDelay), reverbTime, damping);
			_fixedDelays[1] = new FDNDelay((int)round(0.816490 * _largestDelay), reverbTime, damping);
			_fixedDelays[2] = new FDNDelay((int)round(0.707100 * _largestDelay), reverbTime, damping);
			_fixedDelays[3] = new FDNDelay((int)round(0.632450 * _largestDelay), reverbTime, damping);
		}

		Room::~Room() {
			for (int i = 0; i < NUMBER_OF_FDN_DELAYS; i++) {
				delete _fixedDelays[i];
			}
			delete[] _fixedDelays;
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