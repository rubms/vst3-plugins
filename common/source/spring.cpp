#include "../include/spring.h"

namespace Steinberg {
	namespace RubenVST3 {
		Spring::Spring(float springDelaySeconds, float decay, int sampleRate)
			: _springForthTripBuffer(springDelaySeconds * sampleRate), _springBackTripBuffer(springDelaySeconds * sampleRate) {
			_decay = decay;
			_springForthTripBuffer.fillWithSilence();
			_springBackTripBuffer.fillWithSilence();
		}

		void Spring::push(float sample) {
			_springForthTripBuffer.push((sample + _springBackTripBuffer.peek()) * (1 - _decay));
			_springBackTripBuffer.push(_springForthTripBuffer.peek());
		}

		float Spring::peek() {
			return _springForthTripBuffer.peek();
		}
	}
}