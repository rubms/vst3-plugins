#include "../include/dampeddelay.h"
namespace Steinberg {
	namespace RubenVST3 {
		DampedDelay::DampedDelay(int size, float reverbTime, int samplingRate, float damping) :
			Delay(size, reverbTime, samplingRate),
			_damper(damping)
		{
		}

		float DampedDelay::pop()
		{
			return _damper.damp(this->Delay::pop());
		}

		float DampedDelay::peek()
		{
			return _damper.damp(this->Delay::peek());
		}

		void DampedDelay::flush()
		{
			this->Delay::flush();
			_damper.flush();
		}
	}
}