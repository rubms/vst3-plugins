#pragma once

#include "dampeddelay.h"
#include "damper.h"
#include "diffuser.h"

#define SPEED_OF_SOUND 343.2f
#define NUMBER_OF_FDN_DELAYS 4

namespace Steinberg {
	namespace RubenVST3 {
		class Room
		{
		public:
			Room(int samplingRate,
				float damping,
				float roomSizeMeters,
				float reverbTimeSeconds,
				float earlyReflectionsLevel,
				float tailReflectionsLevel,
				float spread);
			~Room();

			float process(float sample);
		private:
			int _samplingRate;
			float _damping;
			float _roomSize;
			float _reverbTime;
			float _earlyLevel;
			float _tailLevel;
			float _largestDelay;
			Damper _inputDamper;
			DampedDelay** _fixedDelays;
			Delay** _tapDelays;
			Diffuser* _inputDiffuser;
			Diffuser** _outputSerialDiffusers;
			void processHadamardMatrix(float* values);
		};
	}
}