#pragma once

namespace Steinberg {
	namespace HelloWorld {
		class CircularAudioBuffer
		{
		public:
			CircularAudioBuffer(int sizeInSamples);
			~CircularAudioBuffer();

			void push(float sample);
			float pop();
			float peek();
			float sampleAt(int index);
			void fillWithSilence();
		private:
			float* _buffer;
			int _capacity;
			int _newestElement;
			int _oldestElement;
			int _size;

			int normalizeIndex(int index);
		};
	}
}