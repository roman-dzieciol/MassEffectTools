#pragma once

class MEUObject
{
public:
	MEObjectNum NetIndex;
	MENameTableIndex unk; // None for function

	MEUObject();
	~MEUObject();

	friend MEArchive& operator << (MEArchive& A, MEUObject& D)
	{
		A << D.NetIndex;
		return A;
	}
};
