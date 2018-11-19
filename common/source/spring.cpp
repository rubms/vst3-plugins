#include "../include/spring.h"

namespace Steinberg {
	namespace RubenVST3 {
		Spring::Spring(float springDelaySeconds, float reverbTime, int sampleRate, float damping) :
				_springForthTripDelay(springDelaySeconds * sampleRate, reverbTime, sampleRate, damping), 
				_springBackTripDelay(springDelaySeconds * sampleRate, reverbTime, sampleRate, damping) {
			float diffscale = springDelaySeconds * 2 * sampleRate / (210 + 159 + 562 + 410);
			_inputDiffuser = new Diffuser(diffscale * 210, 0.75);
			_outputDiffusers = new Diffuser*[3];
			_outputDiffusers[0] = new Diffuser(diffscale * (210 + 159), 0.75);
			_outputDiffusers[1] = new Diffuser(diffscale * (210 + 159 + 562), 0.625);
			_outputDiffusers[2] = new Diffuser(diffscale * (210 + 159 + 562 + 410), 0.625);
		}

		Spring::~Spring() {
			delete _inputDiffuser;
			delete[] _outputDiffusers;
		}

		void Spring::push(float sample) {
			sample = _inputDiffuser->diffuse(sample);
			_springForthTripDelay.feed(sample /*+ _springBackTripDelay.peek()*/);
			_springBackTripDelay.feed(_springForthTripDelay.peek());
		}

		float Spring::peek() {
			float output = _springForthTripDelay.peek();
			output = _outputDiffusers[0]->diffuse(output);
			output = _outputDiffusers[1]->diffuse(output);
			output = _outputDiffusers[2]->diffuse(output);
			return output;
		}
	}
}