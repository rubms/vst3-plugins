#pragma once

#include "circularaudiobuffer.h"

namespace Steinberg {
	namespace RubenVST3 {
		class Diffuser
		{
		public:
			Diffuser(int size, float coefficient);

			float diffuse(float sample);
			void flush();
		private:
			float _coefficient;
			CircularAudioBuffer _audioBuffer;
			float flushToZero(float value);
		};
	}
}