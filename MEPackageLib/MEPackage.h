#pragma once

#include <string>
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

	std::string GetNameString(dword i)
	{
		return NameTable.Items[i].Name;
	}

	std::string GetNameString(MENameIndex nameIndex)
	{
		auto name = GetNameString(nameIndex.Name);
		if (nameIndex.Number != 0) {
			name += MEFormat("%d", nameIndex.Number);
		}
		return name;
	}

	std::string GetObjectName(MEObjectIndex r)
	{
		if (r.Value > 0)			return GetNameString(ExportTable.Items[r.Value - 1].ObjectName);
		else if (r.Value < 0)		return GetNameString(ImportTable.Items[-r.Value - 1].ObjectName);
		else						return "";
	}

	std::string GetObjectPath(MEObjectIndex r);


	MEObjectIndex GetSuperClass(MEObjectIndex r)
	{
		if (r.Value == 0)
			return MEObjectIndex(0);

		if (r.Value > 0)
		{
			r = ExportTable.Items[r.Value - 1].OuterObject;
		}
		else
		{
			r = ImportTable.Items[-r.Value - 1].OuterIndex;
		}
		return r;
	}

};

