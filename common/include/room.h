#pragma once

#include "circularaudiobuffer.h"
#include "reflection.h"

namespace Steinberg {
	namespace RubenVST3 {
		class Room
		{
		public:
			Room(float size, float decay, int sampleRate);
			~Room();

			void feedWithHadamardFeedbackMatrix(float sample);
			float listenSample();
		private:
			int _numBuffers;
			CircularAudioBuffer** _audioBuffers;
			float _size;
			int _sampleRate;
			float _decay;
			int hadamardMatrix[4][4] = {{1, 1, 1, 1}, {1, -1, 1, -1}, {1, 1, -1, -1}, {1, -1, -1, 1} };
		};
	}
}