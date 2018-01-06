#pragma once
#include "MEExporter.h"
#include <iostream>

class MEExporterSQL :
	public MEExporter
{
public:
	std::ostream& s;

	MEExporterSQL(std::ostream& s) : s(s) {
	}
	virtual ~MEExporterSQL();
	virtual void ExportPackage(MEPackage& Package) override;
};

