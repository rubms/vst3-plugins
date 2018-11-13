#include "../include/diffuser.h"

namespace Steinberg {
	namespace RubenVST3 {
		Diffuser::Diffuser(int size, float coefficient)
			: _audioBuffer(size)
		{
			_coefficient = coefficient;
			_audioBuffer.fillWithSilence();
		}

		float Diffuser::diffuse(float sample)
		{
			float result, w;

			w = sample - _audioBuffer.peek() * _coefficient;
			w = flushToZero(w);
			result = _audioBuffer.peek() + w * _coefficient;
			_audioBuffer.push(w);
		
			return(result);
		}

		void Diffuser::flush()
		{
			_audioBuffer.fillWithSilence();
		}

		typedef union {
			float f;
			int i;
		} ls_pcast32;

		float Diffuser::flushToZero(float value)
		{
			ls_pcast32 v;

			v.f = value;

			// original: return (v.i & 0x7f800000) == 0 ? 0.0f : f;
			// version from Tim Blechmann
			return (v.i & 0x7f800000) < 0x08000000 ? 0.0f : value;
		}
	}
}