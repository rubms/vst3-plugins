#pragma once

#include "delay.h"
#include "damper.h"

namespace Steinberg {
	namespace RubenVST3 {
		class DampedDelay: public Delay 
		{
		public:
			DampedDelay(int size, float reverbTime, int samplingRate, float damping);
			virtual float pop();
			virtual float peek();
			virtual void flush();
		private:
			Damper _damper;
		};
	}
}