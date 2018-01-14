#pragma once
//case 0x([0 - 9A - F] + ) : \s +// EX_([A-Za-z]+).*\r?\n.*\r?\n.*\r?\n.*RB_TOKEN_DESC\((.*)\)

#include "METokenFactory.h"

class METoken;

class MEScriptContext {
public:
	dword Depth = 0;
	dword ScriptOffset;
	dword ScriptSize;
};

class MEScript
{
public:
	MEScript();
	~MEScript();

	METokenFactory factory;

	std::vector<std::unique_ptr<METoken>> ParseUntilEnd(MEArchive& A, MEScriptContext& Context);
	std::unique_ptr<METoken> ParseCode(byte code, MEArchive& A, MEScriptContext& Context);
	std::unique_ptr<METoken> ParseFunc(MENativeFuncIndex funcCode, MEArchive& A, MEScriptContext& Context);
	std::vector<std::unique_ptr<METoken>> ParseFuncArgs(MEArchive& A, MEScriptContext& Context);
	std::unique_ptr<METoken> ParseToken(byte code, MEArchive& A, MEScriptContext& Context);
	std::unique_ptr<METoken> ParseToken(MEArchive& A, MEScriptContext& Context);

	void PrintOffsetInfo(std::string Info, MEArchive& A, MEScriptContext& Context);
	void VerifyToken(METoken* Token, MEExprToken Value);
};

