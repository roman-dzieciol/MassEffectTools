#include "stdafx.h"
#include "MEUtils.h"
#include <array>

auto& GMELog = MELog<1024 * 20>::Shared();

void ME::Log(const char *format, ...) {
	va_list args1;
	va_start(args1, format);
	GMELog.Logv(format, args1);
	va_end(args1);
}

extern std::string ME::LogStr() {
	return GMELog.String();
}

std::string MEFormat(const char *format, ...)
{
	va_list args1;
	va_start(args1, format);
	va_list args2;
	va_copy(args2, args1);
	auto size = vsnprintf(NULL, 0, format, args1);
	std::string output(size+1, ' ');
	va_end(args1);
	vsnprintf_s(&output[0], size+1, size+1, format, args2);
	output.resize(size);
	va_end(args2);

	return output;
}

