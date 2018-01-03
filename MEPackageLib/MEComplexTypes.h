#pragma once

#include <string>
#include "MEArchive.h"
#include "MEBasicTypes.h"

// ============================================================================
//  MEString
// ============================================================================
class MEString
{
public:
	operator std::string() const { return Text; }

public:
	friend void operator << (MEArchive& A, MEString& D);

private:
	std::string Text;
};

// ============================================================================
//  MEGUID
// ============================================================================
class MEGUID
{
public:
	friend void operator << (MEArchive& A, MEGUID& D);

private:
	dword Data[4];
};

// ============================================================================
//  MEASCIIZ
// ============================================================================
class MEASCIIZ
{
public:
	operator std::string() const { return Text; }

public:
	friend void operator << (MEArchive& A, MEASCIIZ& D);

private:
	std::string Text;
};

// ============================================================================
//  MEUNICODEZ
// ============================================================================
class MEUNICODEZ
{
public:
	operator std::string() const { return Text; }

public:
	friend void operator << (MEArchive& A, MEUNICODEZ& D);

private:
	std::string Text;
};

// ============================================================================
//  MEFArray
// ============================================================================
template<typename T>
class MEFArray
{
public:
	dword Count() const { return Values.size(); }
	std::vector<T>& Array() const { return Values; }

	friend void operator << (MEArchive& A, MEFArray<T>& D)
	{
		dword count;
		A << count;
		if (count > 1000000) {
			throw MEException("MEFArray count too big: %d, %s", count, A.DebugInfo().c_str());
		}

		D.Values.clear();

		for (dword i = 0; i != count; ++i) {
			auto value = T();
			A << value;
			D.Values.push_back(value);
		}
	}

private:
	std::vector<T> Values;
};

class MENameTableItem {

	MEString Name;
	qword Flags;

	friend void operator << (MEArchive& A, MENameTableItem& D)
	{
		A << D.Name;
		A << D.Flags;
	}
};

class MENameTable : public MEFArray<MENameTableItem> {
};