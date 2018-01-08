#include "stdafx.h"
#include "MEPackage.h"
#include <sstream>

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

	RawObjects.reserve(Header.ExportCount);
	for (auto& item : ExportTable.Items) {
		std::vector<byte> rawObject(item.SerialSize);
		A.Seek(item.SerialOffset);
		A.Serialize(&rawObject[0], item.SerialSize);
		RawObjects.push_back(rawObject);
	}
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


std::string MEPackage::GetObjectPath(MEObjectIndex r)
{
	std::string S;

	if (r.IsNone())
		return "";

	// object name
	S = GetObjectName(r);
	r = GetSuperClass(r);
	if (r.IsNone())
		return S;

	// package path
	const int MaxPackagePath = 255;
	for (int i = 0; i != MaxPackagePath; ++i)
	{
		auto outer = GetObjectName(r);
		S = MEFormat("%s.%s", outer.c_str(), S.c_str());
		r = GetSuperClass(r);
		if (r.IsNone())
			return S;
	}

	throw MEException("Object path depth > %d", MaxPackagePath);
}


