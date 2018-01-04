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

	friend MEArchive& operator << (MEArchive& A, MECompressedChunkInfo& D)
	{
		A << D.UncompressedOffset;
		A << D.UncompressedSize;
		A << D.CompressedOffset;
		A << D.CompressedSize;
		return A;
	}
};


struct FCompressedChunkBlock
{
	dword CompressedSize;
	dword UncompressedSize;

	friend MEArchive& operator << (MEArchive& A, FCompressedChunkBlock& D)
	{
		A << D.CompressedSize;
		A << D.UncompressedSize;
		return A;
	}
};

struct FCompressedChunkHeader
{
	dword Signature;          // equals to PACKAGE_FILE_TAG (0x9E2A83C1)
	dword BlockSize;          // maximal size of uncompressed block, always the same
	FCompressedChunkBlock Summary;
	std::vector<FCompressedChunkBlock> Blocks;

	friend MEArchive& operator << (MEArchive& A, FCompressedChunkHeader& D)
	{
		A << D.Signature;
		A << D.BlockSize;
		A << D.Summary;

		auto blockCount = (D.Summary.UncompressedSize + D.BlockSize - 1) / D.BlockSize;
		for (dword i = 0; i != blockCount; ++i) {
			FCompressedChunkBlock block;
			A << block;
			D.Blocks.push_back(block);
		}
		return A;
	}
};

