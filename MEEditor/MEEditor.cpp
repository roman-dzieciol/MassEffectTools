
#include "MEEditor.h"
#include "MEPackage.h"
#include "MENativeFunctionTable.h"

MEEditor::MEEditor() {

	EditorPackages = {
		"Core",
		"Engine",
		"GameFramework",
		"Editor",
		"UnrealEd",
		"UnrealScriptTest",
		"IpDrv",
	};

	Extensions = {
		"u",
		"upk"
	};

}

fs::path MEEditor::PathForPackage(std::string packageName, fs::path directory) {
	for (auto extension: Extensions)
	{
		auto packagePath = directory / (packageName + "." + extension);
		if (fs::exists(packagePath))
		{
			return packagePath;
		}
	}
	throw MEException("Unknown package %s", packageName.c_str());
}

void MEEditor::LoadPackages(fs::path Path)
{
	MENativeFunctionTable *functionTable = new MENativeFunctionTable();
	std::vector<std::unique_ptr< MEPackage >> packages;

	for (auto&& packageName : EditorPackages)
	{
		auto packagePath = PathForPackage(packageName, Path);
		MEPackageLoader loader;
		auto pkg = loader.Load(packagePath, functionTable);
		packages.push_back(std::move(pkg));

	}
}

