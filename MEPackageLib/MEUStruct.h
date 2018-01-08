#pragma once

#include "MEUField.h"
#include "MEFPropertyTag.h"

class MEUStruct : public MEUField
{
public:
	MEFPropertyTag Tag; // ? 0 0
	MEObjectIndex Super;
	MEObjectIndex ChildIndex;
	dword unk1; // 0
	dword unk2; //
	dword unk3; // 0
	dword unk4; //
	dword ScriptSize; // 0
	std::vector<byte> ByteCode;

	MEUStruct();
	~MEUStruct();

	void SerializeSuperStruct(MEArchive& A, MEUStruct&) {

	}

	friend MEArchive& operator << (MEArchive& A, MEUStruct& D)
	{
		A << static_cast<MEUField&>(D);
		A << D.Tag;

		if (D.Tag.Type.Name.Value != 0) {
			throw MENotImplemented();
		}

		A << D.Super;
		A << D.ChildIndex;
		A << D.unk1;
		A << D.unk2;
		A << D.unk3;
		A << D.unk4;
		A << D.ScriptSize;
		if (D.ScriptSize > 0) {
			D.ByteCode.reserve(D.ScriptSize);
			D.ByteCode.resize(D.ScriptSize);
			A.Serialize(&D.ByteCode[0], D.ScriptSize);
		}


		return A;
	}
};
