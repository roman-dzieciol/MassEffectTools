// MEPackageCmd.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MEPackageLib.h"


int main()
{
	MEPackageLoader loader;
	loader.Load(fs::path("C:\\_MECoop\\Core.u"));
    return 0;
}

