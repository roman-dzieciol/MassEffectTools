#include "stdafx.h"
#include "MEUStruct.h"
#include "MEFLinker.h"
#include "MEPackage.h"


MEUStruct::MEUStruct()
{
}


MEUStruct::~MEUStruct()
{
}

void MEUStruct::Serialize(MEArchive& A)
{
	Super::Serialize(A);

	A << Tag;

	if (A.GetLinker()->GetPackage()->GetNameString(Tag.Type.Name) != "None") {
		throw MENotImplemented();
	}

	A << SuperStruct;
	A << ChildIndex;
	A << unk1;
	A << unk2;
	A << unk3;
	A << unk4;
	A << unk5;
	A << ScriptSize;
	if (ScriptSize > 0) {
		ByteCode.reserve(ScriptSize);
		ByteCode.resize(ScriptSize);
		A.Serialize(&ByteCode[0], ScriptSize);
	}
}