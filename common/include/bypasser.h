#pragma once

#include "pluginterfaces/vst/ivstaudioprocessor.h"

namespace Steinberg {
	namespace RubenVST3 {
		class ByPasser
		{
		public:
			void byPass(Vst::ProcessData & data, int32 numberOfChannels);
		};
	}
}