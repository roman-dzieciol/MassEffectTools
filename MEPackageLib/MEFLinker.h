#pragma once


class MEFLinker
{
public:
	MEFLinker(MEPackage *Package);
	~MEFLinker();

	MEPackage *GetPackage() { return Package; }
private:
	MEPackage *Package;
};

