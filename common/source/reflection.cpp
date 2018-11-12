#include "../include/reflection.h"
#include <cstdlib>

namespace Steinberg {
	namespace HelloWorld {
		Reflection::Reflection(CircularAudioBuffer* audioBuffer, int sampleOffset, float decay) {
			_audioBuffer = audioBuffer;
			_sampleOffset = sampleOffset;
			_decay = decay;
		}

		float Reflection::listen() {
			return _audioBuffer->sampleAt(_sampleOffset) * _decay;
		}
	}
}