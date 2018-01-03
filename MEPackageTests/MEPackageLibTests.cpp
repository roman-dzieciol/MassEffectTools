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
			MEFileReader f(fs::path("C:\\_MECoop\\Core.u"));
			auto pkg = MEPackage();

			f << pkg;
		}

	};
}