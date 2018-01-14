#include "stdafx.h"
#include "METokens.h"
#include "MEUFunction.h"



MEExprToken MENativeFuncToken::GetCode()
{
	return MEExprToken::EX_Extended;
}

std::string MENativeFuncToken::GetName()
{
	return Function->GetObjectName();
}

std::string MENativeFuncToken::GetDescription()
{
	return Function->GetObjectName();
}

void MENativeFuncToken::Parse(MEArchive& A, MEScript& S)
{
	//__debugbreak();

	Tokens = S.ParseFuncArgs(A);
}