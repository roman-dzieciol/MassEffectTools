#include "stdafx.h"
#include "METokens.h"
#include "MEUFunction.h"


MEExprToken ME_EX_HighNative::GetCode()
{
	return Index;
}

std::string ME_EX_HighNative::GetName()
{
	return MEFormat("EX_HighNative_%0.2x", Index);
}

std::string ME_EX_HighNative::GetDescription()
{
	return GetName();
}

void ME_EX_HighNative::Parse(MEArchive& A, MEScript& S, MEScriptContext& Context)
{
	//__debugbreak();

	Tokens = S.ParseFuncArgs(A, Context);
}

MEExprToken MENativeFuncToken::GetCode()
{
	return MEExprToken::EX_ExtendedNative;
}

std::string MENativeFuncToken::GetName()
{
	return Function->GetObjectName();
}

std::string MENativeFuncToken::GetDescription()
{
	return Function->GetObjectName();
}

void MENativeFuncToken::Parse(MEArchive& A, MEScript& S, MEScriptContext& Context)
{
	//__debugbreak();

	Tokens = S.ParseFuncArgs(A, Context);
}