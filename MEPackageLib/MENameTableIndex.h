#pragma once

class MENameTableIndex {
public:
	dword Value;

	explicit MENameTableIndex(int32 value = 0) : Value(value) {}

	friend MEArchive& operator << (MEArchive& A, MENameTableIndex& D)
	{
		A << D.Value;
		D.Verify(A);
		return A;
	}

	void Verify(MEArchive& A);
};