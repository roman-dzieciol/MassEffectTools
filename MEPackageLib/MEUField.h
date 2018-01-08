#pragma once

#include "MEUObject.h"

class MEUField : public MEUObject
{
public:
	MEObjectIndex Next;

	MEUField();
	~MEUField();


	friend MEArchive& operator << (MEArchive& A, MEUField& D)
	{
		A << static_cast<MEUObject&>(D);
		A << D.Next;
		return A;
	}
};