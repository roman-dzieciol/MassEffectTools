#pragma once

#include "MEUField.h"
#include "MEFPropertyTag.h"

class MEUStruct : public MEUField
{
public:
	typedef MEUField Super;

	MEFPropertyTag Tag; // ? 0 0
	MEObjectIndex SuperStruct;
	MEObjectIndex ChildIndex;
	dword unk1; // 0
	dword unk2; //
	dword unk3; // 0
	dword unk4; //
	dword unk5; //
	dword ScriptSize; //
	std::vector<byte> ByteCode;

	MEUStruct();
	~MEUStruct();

	void SerializeSuperStruct(MEArchive& A, MEUStruct&) {

	}

	virtual void Serialize(MEArchive& A) override;
};
