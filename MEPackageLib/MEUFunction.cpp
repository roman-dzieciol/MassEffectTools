#include "stdafx.h"
#include "MEUFunction.h"
#include "MEFLinker.h"


MEUFunction::MEUFunction()
{
}


MEUFunction::~MEUFunction()
{
}

void MEUFunction::Serialize(MEArchive& A)
{
	Super::Serialize(A);

	A << NativeIndex;
	A << OperatorPrecedence;
	A << Flags;
	A << Name;

	if (Flags.is(EFunctionFlags::FUNC_Native) && NativeIndex > 0) {
		A.GetLinker()->AddNativeFunc(NativeIndex, this);
	}
}
