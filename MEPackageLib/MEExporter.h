#pragma once

#include "MEPackage.h"

class MEExporter
{
public:
	MEExporter();
	virtual ~MEExporter();

	virtual void ExportPackage(MEPackage& Package) = 0;
};

