#include "stdafx.h"
#include "MEExporterSQL.h"
#include <sstream>



MEExporterSQL::~MEExporterSQL()
{
}

inline std::string SQLSafe(const std::string& s) {
	if (!s.empty()) {
		return std::string("'") + s + "'";
	}
	return "''";
}

void MEExporterSQL::ExportPackage(MEPackage& Package) {

	//s << "CREATE DATABASE me;" << std::endl;

	s << "BEGIN TRANSACTION;";
	s << std::endl;
	
	s << "CREATE TABLE NameTable (";
	s << "rowid INTEGER PRIMARY KEY,";
	s << "Flags INTEGER,";
	s << "Name TEXT";
	s << ");";
	s << std::endl;
	{
		auto rowid = 0;
		for (auto& item : Package.NameTable.Items) {
			s << "INSERT INTO NameTable VALUES(";
			s << rowid++;
			s << "," << item.Flags;
			s << "," << SQLSafe(static_cast<std::string>(item.Name));
			s << ");";
			s << std::endl;
		}
	}


	s << "CREATE TABLE ImportTable (";
	s << "rowid INTEGER PRIMARY KEY,";
	s << "_Path TEXT,";
	s << "_Package TEXT,";
	s << "_Class TEXT,";
	s << "_Outer TEXT,";
	s << "_Object TEXT,";
	s << "PackageName INTEGER,";
	s << "PackageNameNum INTEGER,";
	s << "ClassName INTEGER,";
	s << "ClassNameNum INTEGER,";
	s << "OuterIndex INTEGER,";
	s << "ObjectName INTEGER,";
	s << "ObjectNameNum INTEGER";
	s << ");";
	s << std::endl;
	{
		auto rowid = 0;
		for (auto& item : Package.ImportTable.Items) {
			s << "INSERT INTO ImportTable VALUES(";
			s << rowid++;
			auto a = SQLSafe(Package.GetObjectPath(MEObjectIndex(-rowid)));
			s << "," << SQLSafe(Package.GetObjectPath(MEObjectIndex(-rowid)));
			s << "," << SQLSafe(Package.GetNameString(item.PackageName));
			s << "," << SQLSafe(Package.GetNameString(item.ClassName));
			s << "," << SQLSafe(Package.GetObjectName(item.OuterIndex));
			s << "," << SQLSafe(Package.GetNameString(item.ObjectName));
			s << "," << item.PackageName.Name;
			s << "," << item.PackageName.Number;
			s << "," << item.ClassName.Name;
			s << "," << item.ClassName.Number;
			s << "," << item.OuterIndex.Value;
			s << "," << item.ObjectName.Name;
			s << "," << item.ObjectName.Number;
			s << ");";
			s << std::endl;
		}
	}


	s << "CREATE TABLE ExportTable (";
	s << "rowid INTEGER PRIMARY KEY,";
	s << "_Path TEXT,";
	s << "_Class TEXT,";
	s << "_Super TEXT,";
	s << "_Outer TEXT,";
	s << "_Object TEXT,";
	s << "_Archetype TEXT,";
	s << "ClassObject INTEGER,";
	s << "SuperObject INTEGER,";
	s << "OuterObject INTEGER,";
	s << "ObjectName INTEGER,";
	s << "ObjectNameNum INTEGER,";
	s << "ArchetypeObject INTEGER,";
	s << "ObjectFlags INTEGER,";
	s << "SerialSize INTEGER,";
	s << "SerialOffset INTEGER,";
	s << "Components TEXT,";
	s << "ExportFlags INTEGER,";
	s << "NetObjects TEXT,";
	s << "PackageGUID TEXT,";
	s << "PackageFlags INTEGER";
	s << ");";
	s << std::endl;
	{
		auto rowid = 0;
		for (auto& item : Package.ExportTable.Items) {
			s << "INSERT INTO ExportTable VALUES(";
			s << rowid++;
			s << "," << SQLSafe(Package.GetObjectPath(MEObjectIndex(rowid)));
			s << "," << SQLSafe(Package.GetObjectName(item.ClassObject));
			s << "," << SQLSafe(Package.GetObjectName(item.SuperObject));
			s << "," << SQLSafe(Package.GetObjectName(item.OuterObject));
			s << "," << SQLSafe(Package.GetNameString(item.ObjectName));
			s << "," << SQLSafe(Package.GetObjectName(item.ArchetypeObject));
			s << "," << item.ClassObject.Value;
			s << "," << item.SuperObject.Value;
			s << "," << item.OuterObject.Value;
			s << "," << item.ObjectName.Name;
			s << "," << item.ObjectName.Number;
			s << "," << item.ArchetypeObject.Value;
			s << "," << item.ObjectFlags;
			s << "," << item.SerialSize;
			s << "," << item.SerialOffset;
			s << "," << SQLSafe("");
			s << "," << item.ExportFlags;
			s << "," << SQLSafe("");
			s << "," << SQLSafe("");// << item.PackageGUID.String());
			s << "," << item.PackageFlags;
			s << ");";
			s << std::endl;
		}
	}

	s << "COMMIT;";
	s << std::endl;
}