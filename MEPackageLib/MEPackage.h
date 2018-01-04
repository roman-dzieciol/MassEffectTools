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

	MEPackage();
	~MEPackage();
	
	virtual void SerializeHeader(MEArchive& A);
	virtual void SerializeContents(MEArchive& A);

	friend void operator << (MEArchive& A, MEPackage& D);

};

