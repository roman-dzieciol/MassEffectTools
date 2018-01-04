#include "stdafx.h"
#include "CppUnitTest.h"
#include "MEPackageLib.h"
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MEPackageTests
{		
	TEST_CLASS(PackageLoading)
	{
	public:
		
		TEST_METHOD(TestItLoadsCore)
		{
			MEPackageLoader loader;
			loader.Load(fs::path("C:\\_MECoop\\Core.u"));
		}

	};
}