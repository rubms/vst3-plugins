#pragma once

#include "fdndelay.h"
#include "damper.h"

#define SPEED_OF_SOUND 343.2f
#define NUMBER_OF_FDN_DELAYS 4

namespace Steinberg {
	namespace RubenVST3 {
		class Room
		{
		public:
			Room(int sampleRate,
				float damping,
				float roomSize,
				float reverbTime,
				float earlyReflectionsLevel,
				float tailReflectionsLevel,
				float inputBandWith);
			~Room();

			void feedWithHadamardFeedbackMatrix(float sample);
			float listenSample();
		private:
			FDNDelay** _fixedDelays;
			int _sampleRate;
			float _damping;
			float _roomSize;
			float _reverbTime;
			float _earlyReflectionsLevel;
			float _tailReflectionsLevel;
			float _largestDelay;
			float _inputBandWith;
			Damper _inputDamper;
			int hadamardMatrix[4][4] = {{1, 1, 1, 1}, {1, -1, 1, -1}, {1, 1, -1, -1}, {1, -1, -1, 1} };
		};
	}
}