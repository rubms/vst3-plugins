#pragma once

namespace Steinberg {
	namespace RubenVST3 {
		class Damper
		{
		public:
			Damper(float damping);

			float damp(float sample);
			void flush();
		private:
			float _damping;
			float _delay;
		};
	}
}