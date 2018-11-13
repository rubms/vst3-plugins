#include "../include/damper.h"

namespace Steinberg {
	namespace RubenVST3 {
		Damper::Damper(float damping)
		{
			_delay = 0.0f;
			_damping = damping;
		}

		float Damper::damp(float sample)
		{
			float result;

			result = sample * (1.0 - _damping) + _delay * _damping;
			_delay = result;

			return(result);
		}

		void Damper::flush()
		{
			_delay = 0.0f;
		}
	}
}