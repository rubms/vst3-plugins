#include "../include/room.h"
#include <cstdlib>
#include <algorithm>
#include <cmath>

namespace Steinberg {
	namespace RubenVST3 {
		Room::Room(int samplingRate,
				float damping,
				float roomSize,
				float reverbTime,
				float earlyLevel,
				float tailLevel,
				float inputBandWith,
				float spread) : 
			_inputDamper(1.0 - inputBandWith)
		{
			_samplingRate = samplingRate;
			_damping = damping;
			_roomSize = roomSize;
			_reverbTime = reverbTime;
			_earlyLevel = earlyLevel;
			_tailLevel = tailLevel;

			_largestDelay = _samplingRate * _roomSize / SPEED_OF_SOUND;

			_fixedDelays = new DampedDelay*[NUMBER_OF_FDN_DELAYS];
			_fixedDelays[0] = new DampedDelay((int)round(1.000000 * _largestDelay), reverbTime, damping, samplingRate);
			_fixedDelays[1] = new DampedDelay((int)round(0.816490 * _largestDelay), reverbTime, damping, samplingRate);
			_fixedDelays[2] = new DampedDelay((int)round(0.707100 * _largestDelay), reverbTime, damping, samplingRate);
			_fixedDelays[3] = new DampedDelay((int)round(0.632450 * _largestDelay), reverbTime, damping, samplingRate);

			float diffscale = (float) round(0.632450 * _largestDelay) / (210 + 159 + 562 + 410);
			int b, c, d, e;
			b = 210;
			c = b + 159 + spread * 0.125541;
			d = b + 159 + 562 + 3.0 * spread * 0.854046;
			e = 1341 - d;

			_inputDiffuser = new Diffuser((int)(diffscale * b), 0.75);
			_outputSerialDiffusers = new Diffuser*[3];
			_outputSerialDiffusers[0] = new Diffuser((int)(diffscale * c - b), 0.75);
			_outputSerialDiffusers[1] = new Diffuser((int)(diffscale * d - c), 0.625);
			_outputSerialDiffusers[1] = new Diffuser((int)(diffscale * e), 0.625);

			_tapDelays = new Delay*[NUMBER_OF_FDN_DELAYS];
			_tapDelays[0] = new Delay((int)round(5 + 0.410 * _largestDelay), reverbTime, samplingRate);
			_tapDelays[1] = new Delay((int)round(5 + 0.300 * _largestDelay), reverbTime, samplingRate);
			_tapDelays[2] = new Delay((int)round(5 + 0.155 * _largestDelay), reverbTime, samplingRate);
			_tapDelays[3] = new Delay((int)round(5 + 0.000 * _largestDelay), reverbTime, samplingRate);
		}

		Room::~Room() {
			for (int i = 0; i < NUMBER_OF_FDN_DELAYS; i++) {
				delete _fixedDelays[i];
			}
			delete[] _fixedDelays;

			delete _inputDiffuser;
			for (int i = 0; i < 3; i++) {
				delete _outputSerialDiffusers[i];
			}
			delete[] _outputSerialDiffusers;

			for (int i = 0; i < NUMBER_OF_FDN_DELAYS; i++) {
				delete _tapDelays[i];
			}
			delete[] _tapDelays;
		}

		void Room::feed(float inputSample) {
			if (fabsf(inputSample) > 100000.0f)
				inputSample = 0.0f;

			float alteredInputSample = _inputDamper.damp(inputSample);
			alteredInputSample = _inputDiffuser->diffuse(alteredInputSample);

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