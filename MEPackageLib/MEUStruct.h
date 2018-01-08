#pragma once

#include "MEUField.h"
#include "MEFPropertyTag.h"

class MEUStruct : public MEUField
{
public:
	MEFPropertyTag Tag; // ? 0 0
	MEObjectIndex ChildIndex;
	//dword unk1; // 0
	//dword unk2; // net index
	//dword size; // 0
	std::vector<byte> remaining;

	MEUStruct();
	~MEUStruct();

	friend MEArchive& operator << (MEArchive& A, MEUStruct& D)
	{
		A << static_cast<MEUField&>(D);
		A << D.Tag;

		if (D.Tag.Type.Name.Value != 0) {
			throw MENotImplemented();
		}

		A << D.ChildIndex;


		return A;
	}
};
