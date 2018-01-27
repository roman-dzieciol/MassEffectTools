#pragma once
#include "MEPackageLib.h"

namespace fs = std::experimental::filesystem;

class MELinker;

class MEEditor {
public:
	MEEditor();
	fs::path PathForPackage(std::string packageName, fs::path directory);
	virtual ~MEEditor() {}

	virtual void LoadPackages(fs::path Path);

	std::vector<std::string> EditorPackages;
	std::vector<std::string> Extensions;
};