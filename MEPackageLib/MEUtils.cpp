#include "stdafx.h"
#include "MEUtils.h"

std::string MEFormat(const char *format, ...)
{
	va_list argptr;
	va_start(argptr, format);
	auto size = std::snprintf(nullptr, 0, format, argptr);
	std::string output(size + 1, '\0');
	sprintf_s(&output[0], size, format, argptr);
	va_end(argptr);
	return output;
}
