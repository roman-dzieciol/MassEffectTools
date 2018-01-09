#pragma once

#include "MEUObject.h"

class MEUField : public MEUObject
{
public:
	typedef MEUObject Super;

	MEObjectIndex Next;

	MEUField();
	~MEUField();


	virtual void Serialize(MEArchive& A) override
	{
		Super::Serialize(A);
		A << Next;
	}
};