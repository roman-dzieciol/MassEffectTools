#include "stdafx.h"
#include "MEUFunction.h"
#include "MEFLinker.h"
#include "MENativeFunctionTable.h"
#include <iostream>


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

	if (Flags.is(EFunctionFlags::FUNC_Net))
	{
		A << RepOffset;
	}
	else {
		RepOffset = 0;
	}
	A << Name;

	if (Flags.is(EFunctionFlags::FUNC_Native) && NativeIndex > 0) {
		//std::cout << "##### Add NF " << NativeIndex << " " << Name.Name.Value << std::endl;
		A.GetLinker()->FunctionTable->AddNativeFunc(NativeIndex, this);
	}
}
