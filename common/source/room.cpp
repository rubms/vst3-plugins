#include "../include/room.h"
#include <cstdlib>
#include <algorithm>
#include <cmath>

namespace Steinberg {
	namespace RubenVST3 {
		/**
		 * 
		 */
		Room::Room(int samplingRate,
				float damping,
				float roomSizeMeters,
				float reverbTimeSeconds,
				float earlyLevel,
				float tailLevel,
				float spread) : 
			_inputDamper(damping)
		{
			_samplingRate = samplingRate;
			_damping = damping;
			_roomSize = roomSizeMeters;
			_reverbTime = reverbTimeSeconds;
			_earlyLevel = earlyLevel;
			_tailLevel = tailLevel;

			_largestDelay = _samplingRate * _roomSize / SPEED_OF_SOUND;

			float fixedDelayTimes[NUMBER_OF_FDN_DELAYS] = { 1.000000 , 0.816490, 0.707100, 0.632450 };
			_fixedDelays = new DampedDelay*[NUMBER_OF_FDN_DELAYS];
			for (int i = 0; i < NUMBER_OF_FDN_DELAYS; i++) 
				_fixedDelays[i] = new DampedDelay((int)round(fixedDelayTimes[i] * _largestDelay), reverbTimeSeconds, damping, samplingRate);

			float diffscale = (float) round(0.632450 * _largestDelay) / (210 + 159 + 562 + 410);
			int b, c, d, e;
			b = 210;
			c = b + 159 + spread * 0.125541;
			d = b + 159 + 562 + 3.0 * spread * 0.854046;
			e = 1341 - d;

			_inputDiffuser = new Diffuser((int)(diffscale * b), 0.75);
			_outputSerialDiffusers = new Diffuser*[3];
			_outputSerialDiffusers[0] = new Diffuser((int)(diffscale * (c - b)), 0.75);
			_outputSerialDiffusers[1] = new Diffuser((int)(diffscale * (d - c)), 0.625);
			_outputSerialDiffusers[2] = new Diffuser((int)(diffscale * e), 0.625);

			float tapDelayTimes[NUMBER_OF_FDN_DELAYS] = { 0.410, 0.300, 0.155, 0.000 };
			_tapDelays = new Delay*[NUMBER_OF_FDN_DELAYS];
			for (int i = 0; i < NUMBER_OF_FDN_DELAYS; i++)
				_tapDelays[i] = new Delay((int)round(5 + tapDelayTimes[i] * _largestDelay), reverbTimeSeconds, samplingRate);
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

		float Room::process(float inputSample) {
			float output;

			if (fabsf(inputSample) > 100000.0f)
				inputSample = 0.0f;

			float alteredInputSample = _inputDamper.damp(inputSample);
			alteredInputSample = _inputDiffuser->diffuse(alteredInputSample);

			float fixedDelayOutputs[NUMBER_OF_FDN_DELAYS];
			float tapDelayOutputs[NUMBER_OF_FDN_DELAYS];
			for (int i = 0; i < NUMBER_OF_FDN_DELAYS; i++) {
				fixedDelayOutputs[i] = _fixedDelays[i]->pop();
				tapDelayOutputs[i] = _tapDelays[i]->pop();
				_tapDelays[i]->feed(alteredInputSample);
			}

			output = 0.0f;
			int sign = 1;
			for (int i = 0; i < NUMBER_OF_FDN_DELAYS; i++) {
				output += sign * (_tailLevel * fixedDelayOutputs[i] + _earlyLevel * tapDelayOutputs[i]);
				sign = -sign;
			}
			output += inputSample * _earlyLevel;

			processHadamardMatrix(fixedDelayOutputs);

			for (int i = 0; i < NUMBER_OF_FDN_DELAYS; i++)
				_fixedDelays[i]->feed(fixedDelayOutputs[i] + tapDelayOutputs[i]);

			output = _outputSerialDiffusers[0]->diffuse(output);
			output = _outputSerialDiffusers[1]->diffuse(output);
			output = _outputSerialDiffusers[2]->diffuse(output);

			return output;
		}

		void Room::processHadamardMatrix(float* values) {
			const float dl0 = values[0], dl1 = values[1], dl2 = values[2], dl3 = values[3];

			values[0] = 0.5f*(+dl0 + dl1 - dl2 - dl3);
			values[1] = 0.5f*(+dl0 - dl1 - dl2 + dl3);
			values[2] = 0.5f*(-dl0 + dl1 - dl2 + dl3);
			values[3] = 0.5f*(+dl0 + dl1 + dl2 + dl3);
		}
	}
}