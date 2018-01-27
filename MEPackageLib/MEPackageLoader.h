#pragma once

#include "MEObjectFactory.h"
#include <functional>

namespace fs = std::experimental::filesystem;

class MEUObject;
class MENativeFunctionTable;

class MEPackageLoader
{
public:
	MEObjectFactory ObjectFactory;

public:
	MEPackageLoader();
	~MEPackageLoader();

	std::unique_ptr<MEPackage> Load(fs::path path, MENativeFunctionTable* FunctionTable);
	void LoadObjects(MEFileArchive& A, MEPackage& D);
	void DumpPackage(MEFileArchive& A, MEPackage& D, fs::path path);
	std::unique_ptr<MEFileArchive> UncompressPackage(MEPackage& Package, MEFileArchive& Archive);
};

