#pragma once

#include "circularaudiobuffer.h"
#include "damper.h"

namespace Steinberg {
	namespace RubenVST3 {
		class FDNDelay
		{
		public:
			FDNDelay(int size, float gain, float damping, int samplingRate);
			void feed(float sample);
			float pop();
			float peek();
			void flush();
		private:
			float _gain;
			CircularAudioBuffer _audioBuffer;
			Damper _damper;
		};
	}
}