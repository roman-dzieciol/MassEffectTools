#include "stdafx.h"
#include "MEPackage.h"


MEPackage::MEPackage()
{
}


MEPackage::~MEPackage()
{
}

void MEPackage::SerializeHeader(MEArchive& A) {

	A << Header;
}

void MEPackage::SerializeContents(MEArchive& A) {

	A.Seek(Header.NameOffset);
	NameTable.Items.reserve(Header.NameCount);
	NameTable.Items.resize(Header.NameCount);
	A << NameTable;
}

void operator << (MEArchive& A, MEPackage& D) {
	D.SerializeHeader(A);
	if (D.Header.CompressionFlags == (dword)MECompressionFlags::None) {
		A.SetDecompressed(true);
	}

	if (D.Header.CompressionFlags != (dword)MECompressionFlags::None) {
		if (!A.IsDecompressed()) {
			return;
		}

	}

	D.SerializeContents(A);
}


