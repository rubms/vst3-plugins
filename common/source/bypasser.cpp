#include "../include/bypasser.h"

namespace Steinberg {
	namespace HelloWorld {
		void ByPasser::byPass(Vst::ProcessData & data, int32 numberOfChannels) {
			if (data.numSamples > 0)
			{
				for (int32 channel = 0; channel < numberOfChannels; channel++) {
					float* inputChannel = data.inputs[0].channelBuffers32[channel];
					float* outputChannel = data.outputs[0].channelBuffers32[channel];

					for (int32 sample = 0; sample < data.numSamples; sample++)
					{
						outputChannel[sample] = inputChannel[sample];
					}
				}
			}
		}
	}
}