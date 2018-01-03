#pragma once
class MEPackageGeneration
{
public:
	dword ExportCount;
	dword NameCount;
	dword NetObjectCount;

	MEPackageGeneration();
	~MEPackageGeneration();

	friend void operator << (MEArchive& A, MEPackageGeneration& D)
	{
		A << D.ExportCount;
		A << D.NameCount;
		A << D.NetObjectCount;
	}
};

