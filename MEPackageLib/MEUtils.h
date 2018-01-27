#pragma once
#include <array>
#include <stdarg.h>

extern std::string MEFormat(const char *format, ...);


inline char MESanitizeAscii(char c) {
	if (c >= ' ' && c <= '~') {
		return c;
	} else {
		return '_';
	}
}

template<size_t BufferSize>
class MELog {
public:
	using BufferType = std::array<char, BufferSize>;
	BufferType Buffer;
	size_t Offset;
	size_t Length;

	typename BufferType::iterator begin() {
		return Buffer.begin() + Offset;
	}

	typename BufferType::iterator end() {
		return Buffer.begin() + ((Offset + Length) % BufferSize);
	}

	MELog() : Offset(0), Length(0) {
		Buffer.fill(' ');
	}

	static MELog& Shared() {
		static MELog shared;
		return shared;
	}

	std::string String() {
		auto result = std::string();
		result.reserve(Length);
		auto const prefixLength = std::min(Length, BufferSize - Offset);
		result.append(&*begin(), prefixLength);
		if (Length > prefixLength) {
			result.append(&*Buffer.begin(), Length - prefixLength);
		}
		return result;
	}

	void UpdateOffset(size_t bytesWritten) {
		if (Length == BufferSize)
		{
			Offset = (Offset + bytesWritten) % BufferSize;
		}
		else
		{
			auto const newLength = std::min(Length + bytesWritten, BufferSize);
			auto const offsetEnd = Offset + Length + bytesWritten;
			Offset = (offsetEnd - newLength) % BufferSize;
			Length = newLength;
		}
	}

	void Log(const char *format, ...) {
		va_list args1;
		va_start(args1, format);
		Logv(format, args1);
		va_end(args1);
	}

	void Logv(const char *format, va_list args1) {
		va_list args2;
		va_copy(args2, args1);
		const auto size = vsnprintf(NULL, 0, format, args1);
		const auto sizeWithTerminator = size + 1;

		if (size > 0) {
			const auto remainingBufferSpace = std::distance(end(), Buffer.end());
			if (sizeWithTerminator <= remainingBufferSpace) {
				char replaced = *(end() + size);
				vsnprintf_s(&*end(), sizeWithTerminator, sizeWithTerminator, format, args2);
				UpdateOffset(size);
				*end() = replaced;
			}
			else {
				std::vector<char> output(sizeWithTerminator);
				vsnprintf_s(&output[0], sizeWithTerminator, sizeWithTerminator, format, args2);
				if (size < BufferSize) {
					std::copy(output.begin(), output.begin() + remainingBufferSpace, end());
					std::copy(output.begin() + remainingBufferSpace, output.end() - 1, Buffer.begin());
					UpdateOffset(size);
				}
				else {
					std::copy(output.end() - BufferSize - 1, output.end() - 1, Buffer.begin());
					Offset = 0;
					Length = BufferSize;
				}
			}
		}
		va_end(args2);
	}
};

namespace ME {
	extern void Log(const char *format, ...);
	extern std::string LogStr();
}