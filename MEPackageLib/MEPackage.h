#pragma once

#include "MEPackage.h"
#include "MEPackageHeader.h"
#include "MEComplexTypes.h"

class MEPackage
{
public:

	MEPackageHeader Header;
	MENameTable NameTable;

	MEPackage();
	~MEPackage();
	

	friend void operator << (MEArchive& A, MEPackage& D) {
		A << D.Header;

		//A.Seek(D.Header.NameOffset);
		//A << D.NameTable;
	}

};

