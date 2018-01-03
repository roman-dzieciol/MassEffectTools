#pragma once
class MECompressedChunkInfo
{
public:

	dword UncompressedOffset;
	dword UncompressedSize;
	dword CompressedOffset;
	dword CompressedSize;

	MECompressedChunkInfo();
	~MECompressedChunkInfo();

	std::string DebugInfo() const {
		return MEFormat("UOffset: %0x, USize: %ud, COffset: %0x, CSize: %ud",
			UncompressedOffset, UncompressedSize, CompressedOffset, CompressedSize);
	}

	friend void operator << (MEArchive& A, MECompressedChunkInfo& D)
	{
		A << D.UncompressedOffset;
		A << D.UncompressedSize;
		A << D.CompressedOffset;
		A << D.CompressedSize;
	}
};

