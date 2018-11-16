#include "../include/fdndelay.h"
#include <cmath>
namespace Steinberg {
	namespace RubenVST3 {
		FDNDelay::FDNDelay(int size, float reverbTime, float damping, int samplingRate)	: 
			_audioBuffer(size), 
			_damper(damping)
		{
			float alpha = pow((double)powf(10.0f, -60/20.0f), 1.0/(double)(reverbTime * samplingRate));
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