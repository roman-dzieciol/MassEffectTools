#pragma once
#include "MEUStruct.h"

class MEUFunction: public MEUStruct
{
public:
	typedef MEUStruct Super;

	word NativeIndex;
	byte OperatorPrecedence;
	MEFlags<EFunctionFlags, dword> Flags;
	MEFName Name;

	MEUFunction();
	~MEUFunction();


	virtual void Serialize(MEArchive& A) override;
};