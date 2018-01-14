#pragma once

#include "MEScript.h"

class MEArchive;
class MEUFunction;

class MEFLinker
{
public:

	MEScript Script;

	std::unordered_map<MENativeFuncIndex, MEUFunction*> NativeFunctions;

	MEFLinker(MEPackage *Package);
	~MEFLinker();

	MEPackage *GetPackage() { return Package; }

	void LoadScripts(MEArchive& A);
	void LoadScript(MEArchive& A, MEUFunction* Function);
	void LoadNativeFunctions(MEArchive& A);
	void LoadNonNativeFunctions(MEArchive& A);

	MEUFunction* GetNativeFunc(MENativeFuncIndex Index);
	void AddNativeFunc(MENativeFuncIndex Index, MEUFunction* Func);

private:
	MEPackage *Package;
};

