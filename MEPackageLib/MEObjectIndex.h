#pragma once

class MEObjectIndex {
public:
	int32 Value;

	explicit MEObjectIndex(int32 value = 0) : Value(value) {}

	static MEObjectIndex FromExportIndex(dword value) {
		return MEObjectIndex(value + 1);
	}

	static MEObjectIndex FromImportIndex(dword value) {
		return MEObjectIndex(-(int32)value - 1);
	}

	bool IsExport() const { return Value > 0; }
	bool IsImport() const { return Value < 0; }
	bool IsNone() const { return Value == 0; }

	MEObjectNum GetExportNum() const {
		if (!IsExport()) {
			throw MEException("Not an import table index: %d", Value);
		}
		return Value - 1;
	}

	MEObjectNum GetImportNum() const {
		if (!IsImport()) {
			throw MEException("Not an import table index: %d", Value);
		}
		return -Value - 1;
	}

	friend MEArchive& operator << (MEArchive& A, MEObjectIndex& D)
	{
		A << D.Value;
		D.Verify(A);
		return A;
	}

	void Verify(MEArchive& A);
};
