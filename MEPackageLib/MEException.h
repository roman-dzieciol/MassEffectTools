#pragma once

#include <exception>
#include <cstdarg>
#include <string>
#include <stdio.h>  

class MEException : public std::exception
{
public:
	MEException(const char *format, ...)
	{
		va_list argptr;
		va_start(argptr, format);
		auto size = std::snprintf(nullptr, 0, format, argptr);
		std::string output(size + 1, '\0');
		sprintf_s(&output[0], size, format, argptr);
		va_end(argptr);
	}

	MEException(const MEException& rhs) : m_errorMsg(rhs.m_errorMsg)
	{
	}

	virtual ~MEException()
	{
	}

	MEException& operator=(const MEException& rhs)
	{
		m_errorMsg = rhs.m_errorMsg;
		return *this;
	}

	virtual char const* what() const
	{
		return m_errorMsg.c_str();
	}

private:
	std::string m_errorMsg;
};