#pragma once

#include "circularaudiobuffer.h"

namespace Steinberg {
	namespace HelloWorld {
		class Reflection {
		public :
			Reflection(CircularAudioBuffer* audioBuffer, int sampleOffset, float decay);
			float listen();
		private:
			int _sampleOffset;
			float _decay;
			CircularAudioBuffer* _audioBuffer;
		};
	}
}