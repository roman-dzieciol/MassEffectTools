#include "stdafx.h"
#include "MEObjectIndex.h"
#include "MEFLinker.h"

void MEObjectIndex::Verify(MEArchive& A) {
	if (IsExport()) {
		if (GetExportNum() >= A.GetLinker()->GetPackage()->Header.ExportCount) {
			throw MEException("Invalid export index: %d", Value);
		}
	}
	else if (IsImport()) {
		if (GetImportNum() >= A.GetLinker()->GetPackage()->Header.ImportCount) {
			throw MEException("Invalid import index: %d", Value);
		}
	}
}
