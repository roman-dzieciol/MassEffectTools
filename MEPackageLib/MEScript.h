#pragma once
//case 0x([0 - 9A - F] + ) : \s +// EX_([A-Za-z]+).*\r?\n.*\r?\n.*\r?\n.*RB_TOKEN_DESC\((.*)\)

#include "METokenFactory.h"

class METoken;


class MEScript
{
public:
	MEScript();
	~MEScript();

	METokenFactory factory;
	dword _Indent = 0;

	std::vector<std::unique_ptr<METoken>> ParseUntilEnd(MEArchive& A);
	std::unique_ptr<METoken> ParseCode(byte code, MEArchive& A);
	std::unique_ptr<METoken> ParseFunc(MENativeFuncIndex funcCode, MEArchive& A);
	std::vector<std::unique_ptr<METoken>> ParseFuncArgs(MEArchive& A);
	std::unique_ptr<METoken> ParseToken(byte code, MEArchive& A);
	std::unique_ptr<METoken> ParseToken(MEArchive& A);

	void PrintOffsetInfo(std::string Info, MEArchive& A);
};

