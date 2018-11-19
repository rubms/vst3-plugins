#pragma once

#include "dampeddelay.h"
#include "diffuser.h"

namespace Steinberg {
	namespace RubenVST3 {
		class Spring
		{
		public:
			Spring(float springDelaySeconds, float reverbTime, int sampleRate, float damping);
			~Spring();

			void push(float sample);
			float peek();
		private:
			Diffuser* _inputDiffuser;
			DampedDelay _springForthTripDelay;
			DampedDelay _springBackTripDelay;
			Diffuser** _outputDiffusers;
		};
	}
}