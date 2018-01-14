#pragma once

#include "METoken.h"

class METokenFactory
{
	std::unordered_map<MEExprToken, std::function<std::unique_ptr<METoken>()>> ConstructorMap;

public:
	METokenFactory();
	~METokenFactory();

	std::unique_ptr<METoken> ConstructByCode(MEExprToken Code);

	void RegisterToken(MEExprToken Code, std::function<std::unique_ptr<METoken>()> Constructor);
	void RegisterAll();
};