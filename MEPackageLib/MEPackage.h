#pragma once

#include "MEPackage.h"
#include "MEPackageHeader.h"
#include "MEComplexTypes.h"

class MEPackage
{
public:

	MEPackageHeader Header;

	std::vector<FCompressedChunkHeader> ChunkHeaders;

	MENameTable NameTable;
	MEImportTable ImportTable;
	MEExportTable ExportTable;

	MEPackage();
	~MEPackage();
	

	void SerializeHeader(MEArchive& A);
	void SerializeContents(MEArchive& A);

	friend MEArchive& operator << (MEArchive& A, MEPackage& D);

};

