#pragma once

#include "MEScript.h"

class MEArchive;
class MEUFunction;
class MENativeFunctionTable;

class MEFLinker
{
public:

	MEScript Script;
	MENativeFunctionTable* FunctionTable;

	MEFLinker(MEPackage *Package, MENativeFunctionTable* FunctionTable);
	~MEFLinker();

	MEPackage *GetPackage() { return Package; }

	void LoadScripts(MEArchive& A);
	void LoadScript(MEArchive& A, MEUFunction* Function);
	void LoadNativeFunctions(MEArchive& A);
	void LoadNonNativeFunctions(MEArchive& A);


private:
	MEPackage *Package;
};

