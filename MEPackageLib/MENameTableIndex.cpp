#include "stdafx.h"
#include "MENameTableIndex.h"
#include "MEFLinker.h"

void MENameTableIndex::Verify(MEArchive& A) {
	if (Value >= A.GetLinker()->GetPackage()->Header.NameCount) {
		throw MEException("Invalid name table index: %d", Value);
	}
}
