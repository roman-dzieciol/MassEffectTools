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

	A.Seek(Header.ImportOffset);
	ImportTable.Items.reserve(Header.ImportCount);
	ImportTable.Items.resize(Header.ImportCount);
	A << ImportTable;

	A.Seek(Header.ExportOffset);
	ExportTable.Items.reserve(Header.ExportCount);
	ExportTable.Items.resize(Header.ExportCount);
	A << ExportTable;
}

MEArchive& operator << (MEArchive& A, MEPackage& D) {
	D.SerializeHeader(A);
	if (D.Header.CompressionFlags == (dword)MECompressionFlags::None) {
		A.SetDecompressed(true);
	}

	if (D.Header.CompressionFlags != (dword)MECompressionFlags::None) {
		if (!A.IsDecompressed()) {
			return A;
		}

	}

	D.SerializeContents(A);
	return A;
}


