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
		va_list args1;
		va_start(args1, format);
		va_list args2;
		va_copy(args2, args1);
		auto size = vsnprintf(NULL, 0, format, args1);
		std::string output(size + 1, ' ');
		va_end(args1);
		vsnprintf_s(&output[0], size + 1, size + 1, format, args2);
		output.resize(size);
		va_end(args2);

		m_errorMsg = output;
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

class MENotImplemented : public MEException {
public:
	MENotImplemented() : MEException("Not implemented") {}
};