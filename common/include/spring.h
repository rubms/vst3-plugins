#pragma once

#include "circularaudiobuffer.h"

namespace Steinberg {
	namespace RubenVST3 {
		class Spring
		{
		public:
			Spring(float springDelaySeconds, float decay, int sampleRate);

			void push(float sample);
			float peek();
		private:
			CircularAudioBuffer _springForthTripBuffer;
			CircularAudioBuffer _springBackTripBuffer;
			float _decay;
		};
	}
}