#pragma once

#include "circularaudiobuffer.h"

namespace Steinberg {
	namespace HelloWorld {
		class Spring
		{
		public:
			Spring(int loops, float springDelaySeconds, float decay, int sampleRate);
			~Spring();

			void push(float sample);
			float peek();
		private:
			CircularAudioBuffer** _audioBuffers;
			int _numberOfLoops;
			float _decay;
		};
	}
}