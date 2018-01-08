#pragma once

#include <string>
#include "MEArchive.h"
#include "MEBasicTypes.h"
#include "MEFName.h"
#include "MEObjectIndex.h"
#include "MENameTableIndex.h"
#include "MEFlags.h"

// ============================================================================
//  MEString
// ============================================================================
class MEString
{
public:
	operator std::string() const { return Text; }

public:
	friend MEArchive& operator << (MEArchive& A, MEString& D);

private:
	std::string Text;
};

// ============================================================================
//  MEGUID
// ============================================================================
class MEGUID
{
public:
	friend MEArchive& operator << (MEArchive& A, MEGUID& D);
	std::string String() const;

private:
	dword Data[4];
};

// ============================================================================
//  MEASCIIZ
// ============================================================================
class MEASCIIZ
{
public:
	operator std::string() const { return Text; }

public:
	friend MEArchive& operator << (MEArchive& A, MEASCIIZ& D);

private:
	std::string Text;
};

// ============================================================================
//  MEUNICODEZ
// ============================================================================
class MEUNICODEZ
{
public:
	operator std::string() const { return Text; }

public:
	friend MEArchive& operator << (MEArchive& A, MEUNICODEZ& D);

private:
	std::string Text;
};

// ============================================================================
//  MEFArray
// ============================================================================
template<typename T>
class MEFArray
{
public:
	dword Count() const { return Values.size(); }
	std::vector<T>& Array() { return Values; }

	friend MEArchive& operator << (MEArchive& A, MEFArray<T>& D)
	{
		dword count;
		A << count;
		if (count > 1000000) {
			throw MEException("MEFArray count too big: %d, %s", count, A.DebugInfo().c_str());
		}

		D.Values.clear();

		for (dword i = 0; i != count; ++i) {
			auto value = T();
			A << value;
			D.Values.push_back(value);
		}
		return A;
	}

private:
	std::vector<T> Values;
};

template<typename TK, typename TV>
struct TMapPair
{
	TK		Key;
	TV		Value;

	friend MEArchive& operator<<(MEArchive &Ar, TMapPair &V)
	{
		return Ar << V.Key << V.Value;
	}
};

template<typename TK, typename TV>
class TMap : public MEFArray<TMapPair<TK, TV> >
{
public:
	friend MEArchive& operator<<(MEArchive &Ar, TMap &Map)
	{
		return Ar << (MEFArray<TMapPair<TK, TV> >&)Map;
	}
};

class MENameTableItem {
public:
	MEString Name;
	qword Flags;

	friend MEArchive& operator << (MEArchive& A, MENameTableItem& D)
	{
		A << D.Name;
		A << D.Flags;
		return A;
	}
};

class MENameTable {
public:
	std::vector<MENameTableItem> Items;

	friend MEArchive& operator << (MEArchive& A, MENameTable& D)
	{
		UP_BYTE_MARKER(MEImportTable, A, A.Tell(), BI_NameTable);
		for (auto& item : D.Items) {
			A << item;
		}
		return A;
	}
};





class MEImportTableItem {
public:
	MEFName PackageName;
	MEFName ClassName;
	MEObjectIndex OuterIndex;
	MEFName ObjectName;

	friend MEArchive& operator << (MEArchive& A, MEImportTableItem& D)
	{
		A << D.PackageName;
		A << D.ClassName;
		A << D.OuterIndex;
		A << D.ObjectName;
		return A;
	}
};

class MEImportTable {
public:
	std::vector<MEImportTableItem> Items;

	friend MEArchive& operator << (MEArchive& A, MEImportTable& D)
	{
		UP_BYTE_MARKER(MEImportTable, A, A.Tell(), BI_ImportTable);
		for (auto& item : D.Items) {
			A << item;
		}
		return A;
	}
};

class MEExportTableItem {
public:
	MEObjectIndex ClassObject;
	MEObjectIndex SuperObject;
	MEObjectIndex OuterObject;
	MEFName ObjectName;
	MEObjectIndex ArchetypeObject;
	MEFlags<EObjectFlags, dword> ObjectFlags;
	MEFlags<EObjectFlags, dword> ObjectFlags2;
	dword SerialSize;
	dword SerialOffset;

	TMap<MEFName, MEObjectIndex> Components;

	dword ExportFlags;

	MEFArray<MEObjectIndex> NetObjects;

	MEGUID PackageGUID;
	MEFlags<EPackageFlags, dword> PackageFlags;

	friend MEArchive& operator << (MEArchive& A, MEExportTableItem& D)
	{
		A << D.ClassObject;
		A << D.SuperObject;
		A << D.OuterObject;
		A << D.ObjectName;
		A << D.ArchetypeObject;
		A << D.ObjectFlags;
		A << D.ObjectFlags2;
		A << D.SerialSize;
		A << D.SerialOffset;
		A << D.Components;
		A << D.ExportFlags;
		A << D.NetObjects;
		A << D.PackageGUID;
		A << D.PackageFlags;
		return A;
	}
};

class MEExportTable {
public:
	std::vector<MEExportTableItem> Items;

	friend MEArchive& operator << (MEArchive& A, MEExportTable& D)
	{
		UP_BYTE_MARKER(MEExportTable, A, A.Tell(), BI_ExportTable);
		for (auto& item : D.Items) {
			A << item;
		}
		return A;
	}
};