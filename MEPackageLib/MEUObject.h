#pragma once

class MEUObject
{
public:
	//MEObjectNum NetIndex;
	//MEFName UnkName; // None for function

	dword _TableIndex = 0;
	std::string _Name;


	MEUObject();
	virtual ~MEUObject();

	virtual void Serialize(MEArchive& A) {

	}

	virtual std::string GetObjectName() {
		return _Name;
	}

	friend MEArchive& operator << (MEArchive& A, MEUObject& D)
	{
		//A << D.NetIndex;
		D.Serialize(A);
	}
};
