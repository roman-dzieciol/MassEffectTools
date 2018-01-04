#pragma once

#include <string>
#include "MEArchive.h"
#include "MEBasicTypes.h"

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
		for (auto& item : D.Items) {
			A << item;
		}
		return A;
	}
};


class MENameIndex {
public:
	dword Name;
	dword Number;

	friend MEArchive& operator << (MEArchive& A, MENameIndex& D)
	{
		A << D.Name;
		A << D.Number;
		return A;
	}
};

class MEObjectIndex {
public:
	dword Index;

	friend MEArchive& operator << (MEArchive& A, MEObjectIndex& D)
	{
		A << D.Index;
		return A;
	}
};

class MEImportTableItem {
public:
	MENameIndex PackageName;
	MENameIndex ClassName;
	dword OuterIndex;
	MENameIndex ObjectName;

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
	MENameIndex ObjectName;
	MEObjectIndex ArchetypeObject;
	qword ObjectFlags;
	dword SerialSize;
	dword SerialOffset;

	TMap<MENameIndex, MEObjectIndex> Components;

	dword ExportFlags;

	MEFArray<MEObjectIndex> NetObjects;

	MEGUID PackageGUID;
	dword PackageFlags;

	friend MEArchive& operator << (MEArchive& A, MEExportTableItem& D)
	{
		A << D.ClassObject;
		A << D.SuperObject;
		A << D.OuterObject;
		A << D.ObjectName;
		A << D.ArchetypeObject;
		A << D.ObjectFlags;
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
		for (auto& item : D.Items) {
			A << item;
		}
		return A;
	}
};