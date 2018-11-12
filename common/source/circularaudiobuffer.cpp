#include "../include/circularaudiobuffer.h"

namespace Steinberg {
	namespace HelloWorld {
		CircularAudioBuffer::CircularAudioBuffer(int sizeInSamples) {
			_capacity = sizeInSamples;
			_buffer = new float[sizeInSamples];

			_newestElement = _oldestElement = 0;
			_size = 0;
		}

		CircularAudioBuffer::~CircularAudioBuffer() {
			delete [] _buffer;
		}

		void CircularAudioBuffer::push(float sample) {
			if (_capacity == 0)
				return;

			if (_size == _capacity) {
				this->pop();
			}
			_buffer[_newestElement] = sample;
			_newestElement = normalizeIndex(_newestElement + 1);
			_size++;
		}

		float CircularAudioBuffer::sampleAt(int index) {
			if (_size <= index)
				return 0;
			
			return _buffer[normalizeIndex(_oldestElement + index)];
		}

		void CircularAudioBuffer::fillWithSilence()
		{
			for (int i = 0; i < _capacity; i++)
				push(0);
		}

		int CircularAudioBuffer::normalizeIndex(int index)
		{
			if (_capacity == 0)
				return 0;

			if (index >= _capacity)
				return index % _capacity;
			if (index < 0)
				return index + _capacity;
			return index;
		}

		float CircularAudioBuffer::pop() {
			if (_size == 0)
				return 0;

			float result = _buffer[_oldestElement];
			_oldestElement = normalizeIndex(_oldestElement + 1);
			_size--;
			return result;
		}

		float CircularAudioBuffer::peek() {
			if (_size == 0)
				return 0;

			return _buffer[_oldestElement];
		}
	}
}