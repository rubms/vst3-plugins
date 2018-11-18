#pragma once

#include "circularaudiobuffer.h"
#include "damper.h"

namespace Steinberg {
	namespace RubenVST3 {
		class Delay
		{
		public:
			Delay(int size, float reverbTime, int samplingRate);
			void feed(float sample);
			virtual float pop();
			virtual float peek();
			virtual void flush();
		private:
			float _gain;
			CircularAudioBuffer _audioBuffer;
		};
	}
}