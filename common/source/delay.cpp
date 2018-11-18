#include "../include/delay.h"
#include <cmath>
namespace Steinberg {
	namespace RubenVST3 {
		Delay::Delay(int size, float reverbTime, int samplingRate)	: 
			_audioBuffer(size)
		{
			float alpha = pow((double)powf(10.0f, -60/20.0f), 1.0/(double)(reverbTime * samplingRate));
			_gain = -powf(alpha, size);
			_audioBuffer.fillWithSilence();
		}

		void Delay::feed(float sample)
		{
			_audioBuffer.push(sample);
		}

		float Delay::pop()
		{
			return _audioBuffer.pop() * _gain;
		}

		float Delay::peek()
		{
			return _audioBuffer.peek() * _gain;
		}

		void Delay::flush()
		{
			_audioBuffer.fillWithSilence();
		}
	}
}