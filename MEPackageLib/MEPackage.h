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

	std::vector< std::vector<byte> > RawObjects;

	MEPackage();
	~MEPackage();
	

	void SerializeHeader(MEArchive& A);
	void SerializeContents(MEArchive& A);

	friend MEArchive& operator << (MEArchive& A, MEPackage& D);

	std::string GetNameString(MENameTableIndex i)
	{
		return NameTable.Items.at(i.Value).Name;
	}

	std::string GetNameString(MEFName nameIndex)
	{
		auto name = GetNameString(nameIndex.Name);
		if (nameIndex.Number != 0) {
			name += MEFormat("%d", nameIndex.Number);
		}
		return name;
	}

	MEObjectNum GetObjectNum(const MEObjectIndex index) const {
		if (index.IsExport()) {
			const MEObjectNum num = index.Value - 1;
			if (num < ExportTable.Items.size()) {
				return num;
			}
		}
		else if (index.IsImport()) {
			const MEObjectNum num = -index.Value - 1;
			if (num < ImportTable.Items.size()) {
				return num;
			}
		}
		throw MEException("Invalid Object Index: %d", index.Value);
	}

	std::string GetObjectName(MEObjectIndex r)
	{
		if (r.IsNone())			return "";
		else if (r.IsExport())	return GetNameString(ExportTable.Items[GetObjectNum(r)].ObjectName);
		else if (r.IsImport())	return GetNameString(ImportTable.Items[GetObjectNum(r)].ObjectName);
		throw MEException("MEObjectIndex inconsistency");
	}

	std::string GetObjectPath(MEObjectIndex r);

	MEObjectIndex GetSuperClass(MEObjectIndex r)
	{
		if (r.IsNone())			return r;
		else if (r.IsExport())	return ExportTable.Items[GetObjectNum(r)].OuterObject;
		else if (r.IsImport())	return ImportTable.Items[GetObjectNum(r)].OuterIndex;
		throw MEException("MEObjectIndex inconsistency");
	}



};

