#pragma once
#include <unordered_map>
#include <functional>

class MEUObject;

class MEObjectFactory
{
	std::unordered_map<std::string, std::function<std::unique_ptr<MEUObject>()>> ConstructorMap;

public:
	MEObjectFactory();
	~MEObjectFactory();

	std::unique_ptr<MEUObject> ConstructByClassName(const std::string& ClassName);

	void RegisterConstructor(std::string ClassName, std::function<std::unique_ptr<MEUObject>()> Constructor);
};

