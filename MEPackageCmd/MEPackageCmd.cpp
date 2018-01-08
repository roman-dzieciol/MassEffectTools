// MEPackageCmd.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MEPackageLib.h"
#include <iostream>


int main(int argc, char** argv)
{
	if (argc != 2) {
		std::cerr << "Usage: MEPackageCmd.exe <path>" << std::endl;
		return 1;
	}

	auto path = fs::path(argv[1]);
	if (!fs::exists(path)) {
		std::cerr << "Path does not exist: " << path << std::endl;
		return 1;
	}

	MEPackageLoader loader;
	loader.Load(path);
    return 0;
}

