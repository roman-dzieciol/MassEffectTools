#pragma once

class MEUObject
{
public:
	//MEObjectNum NetIndex;
	//MEFName UnkName; // None for function

	MEUObject();
	virtual ~MEUObject();

	virtual void Serialize(MEArchive& A) {

	}

	friend MEArchive& operator << (MEArchive& A, MEUObject& D)
	{
		//A << D.NetIndex;
		D.Serialize(A);
	}
};
