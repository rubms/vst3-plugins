#include "../include/fdndelay.h"
#include <cmath>
namespace Steinberg {
	namespace RubenVST3 {
		FDNDelay::FDNDelay(int size, float alpha, float damping)	: 
			_audioBuffer(size), 
			_damper(damping)
		{
			_gain = -powf(alpha, size);
			_audioBuffer.fillWithSilence();
		}

		void FDNDelay::feed(float sample)
		{

		}

		float FDNDelay::pop()
		{
			return _audioBuffer.pop();
		}

		float FDNDelay::peek()
		{
			return _audioBuffer.peek();
		}

		void FDNDelay::flush()
		{
			_audioBuffer.fillWithSilence();
		}
	}
}