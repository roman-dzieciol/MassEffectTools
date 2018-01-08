#pragma once

#include "MENameTableIndex.h"

class MEFName {
public:
	MENameTableIndex Name;
	dword Number;

	MEFName();
	~MEFName();

	friend MEArchive& operator << (MEArchive& A, MEFName& D)
	{
		A << D.Name;
		A << D.Number;
		return A;
	}
};