#pragma once

class MEUFunction
{
public:

	word NativeIndex;
	byte OperatorPrecedence;
	MEFlags<EFunctionFlags, dword> Flags;
	MEFName Name;

	MEUFunction();
	~MEUFunction();

	friend MEArchive& operator << (MEArchive& A, MEUFunction& D)
	{
		A << D.NativeIndex;
		A << D.OperatorPrecedence;
		A << D.Flags;
		A << D.Name;
		return A;
	}
};