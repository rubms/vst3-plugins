#pragma once

#include "circularaudiobuffer.h"
#include "reflection.h"

namespace Steinberg {
	namespace HelloWorld {
		class Room
		{
		public:
			Room(float size, float decay, int sampleRate);
			~Room();

			void pushSample(float sample);
			float listenSample();
		private:
			CircularAudioBuffer _audioBuffer;
			float _size;
			int _sampleRate;
			Reflection** _reflections;
		};
	}
}