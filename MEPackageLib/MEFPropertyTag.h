#pragma once

#include "MEFName.h"

class MEFPropertyTag
{
public:
	MEFName Type;
	// TODO

	MEFPropertyTag();
	~MEFPropertyTag();

	friend MEArchive& operator << (MEArchive& A, MEFPropertyTag& D)
	{
		A << D.Type;
		if (D.Type.Name.Value != 0) {
			throw MENotImplemented();
		}
		return A;
	}
};

