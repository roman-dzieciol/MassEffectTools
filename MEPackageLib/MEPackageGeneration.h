#pragma once
class MEPackageGeneration
{
public:
	dword ExportCount;
	dword NameCount;
	dword NetObjectCount;

	MEPackageGeneration();
	~MEPackageGeneration();

	friend MEArchive& operator << (MEArchive& A, MEPackageGeneration& D)
	{
		A << D.ExportCount;
		A << D.NameCount;
		A << D.NetObjectCount;
		return A;
	}
};

