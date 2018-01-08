#pragma once

class MEUFunction
{
public:
	MEUFunction();
	~MEUFunction();

	friend MEArchive& operator << (MEArchive& A, MEUFunction& D)
	{
		return A;
	}
};