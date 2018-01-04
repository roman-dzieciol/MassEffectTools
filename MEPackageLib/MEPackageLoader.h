#pragma once

namespace fs = std::experimental::filesystem;

class MEPackageLoader
{
public:
	MEPackageLoader();
	~MEPackageLoader();

	void Load(fs::path path);
	std::unique_ptr<MEFileArchive> UncompressPackage(MEPackage& Package, MEFileArchive& Archive);
};

