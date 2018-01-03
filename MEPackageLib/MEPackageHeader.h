#pragma once

#include "MEPackageGeneration.h"
#include "MECompressedChunkInfo.h"
#include "MECompression.h"

class MEPackageHeader
{
public:

	dword		Signature;
	word		PackageVersion;
	word		LicenseMode;
	dword		HeaderSize;
	MEString	FolderName;
	dword		PackageFlags;
	dword		NameCount;
	dword		NameOffset;
	dword		ExportCount;
	dword		ExportOffset;
	dword		ImportCount;
	dword		ImportOffset;
	dword		DependsOffset;
	MEGUID		GUID;
	MEFArray<MEPackageGeneration> Generations;
	dword		EngineVersion;
	dword		CookerVersion;
	dword		Unknown1;
	dword		Unknown2;
	dword		Unknown3;
	dword		Unknown4;
	dword		Unknown5;
	dword		Unknown6;
	dword		Unknown7;
	dword		CompressionFlags;
	MEFArray<MECompressedChunkInfo> ChunkInfo;
	dword		Unknown8;
	dword		Unknown9;
	// Unknown


	MEPackageHeader();
	~MEPackageHeader();

	friend void operator << (MEArchive& A, MEPackageHeader& D)
	{
		//UP_BYTE_MARKER(header, A, 0, BI_Header);

		A << D.Signature;
		if (D.Signature != MEConst::signature) {
			throw std::runtime_error("Unknown package signature");
		}

		A << D.PackageVersion;
		if (D.PackageVersion != MEConst::packageVersion) {
			throw std::runtime_error("Unknown package version");
		}

		A << D.LicenseMode;
		if (D.LicenseMode != MEConst::licenseMode) {
			throw std::runtime_error("Unknown license mode");
		}

		A << D.HeaderSize;
		A << D.FolderName;
		A << D.PackageFlags;
		A << D.NameCount;
		A << D.NameOffset;
		A << D.ExportCount;
		A << D.ExportOffset;
		A << D.ImportCount;
		A << D.ImportOffset;
		A << D.DependsOffset;
		A << D.GUID;
		A << D.Generations;
		A << D.EngineVersion;
		A << D.CookerVersion;
		A << D.Unknown1;
		A << D.Unknown2;
		A << D.Unknown3;
		A << D.Unknown4;
		A << D.Unknown5;
		A << D.Unknown6;
		A << D.Unknown7;
		A << D.CompressionFlags;
		if (D.CompressionFlags != static_cast<dword>(MECompressionFlags::None)) {
			A << D.ChunkInfo;
		}
		A << D.Unknown8;
		A << D.Unknown9;
	}
};

