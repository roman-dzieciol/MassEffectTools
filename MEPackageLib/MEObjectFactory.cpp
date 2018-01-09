#include "stdafx.h"
#include "MEObjectFactory.h"
#include "MEUFunction.h"
#include <iostream>


MEObjectFactory::MEObjectFactory()
{
	RegisterConstructor("Function", []()->std::unique_ptr<MEUObject> { return std::make_unique<MEUFunction>(); });
}


MEObjectFactory::~MEObjectFactory()
{
}

std::unique_ptr<MEUObject> MEObjectFactory::ConstructByClassName(const std::string& ClassName) {
	auto result = ConstructorMap.find(ClassName);
	if (result != ConstructorMap.end()) {
		return result->second();
	}
	else {
		//std::cerr << "ConstructByClassName: Unknown class " << ClassName << std::endl;
	}
	return {};
}

void MEObjectFactory::RegisterConstructor(std::string ClassName, std::function<std::unique_ptr<MEUObject>()> Constructor) {
	ConstructorMap[ClassName] = Constructor;
}