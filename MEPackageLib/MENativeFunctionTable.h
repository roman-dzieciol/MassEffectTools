#pragma once

class MEUFunction;

class MENativeFunctionTable
{
public:
	MENativeFunctionTable();
	~MENativeFunctionTable();


	std::unordered_map<MENativeFuncIndex, MEUFunction*> NativeFunctions;
	MEUFunction* GetNativeFunc(MENativeFuncIndex Index);
	void AddNativeFunc(MENativeFuncIndex Index, MEUFunction* Func);
};

