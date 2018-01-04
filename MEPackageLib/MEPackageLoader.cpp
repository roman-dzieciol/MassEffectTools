#include "stdafx.h"
#include "MEPackageLoader.h"


MEPackageLoader::MEPackageLoader()
{
}


MEPackageLoader::~MEPackageLoader()
{
}


void MEPackageLoader::Load(fs::path path) {

	MEFileArchive f;
	f.ReadPath(fs::path("C:\\_MECoop\\Core.u"));
	auto pkg = MEPackage();
	f << pkg;

	if (pkg.Header.CompressionFlags != (dword)MECompressionFlags::None && !f.IsDecompressed()) {
		//f.Decompress(pkg.Header.ChunkInfo.Array(), static_cast<MECompressionFlags>(pkg.Header.CompressionFlags));
		auto uncompressed = UncompressPackage(pkg, f);
		auto uncompressedPackage = MEPackage();
		uncompressedPackage.Header = pkg.Header;
		uncompressedPackage.Header.CompressionFlags = 0;
		uncompressedPackage.Header.ChunkInfo.Array().clear();
		uncompressedPackage.SerializeContents(*uncompressed);
		
		//f.SetDecompressed(true);
		//f << pkg;
	}
}

std::unique_ptr<MEFileArchive> MEPackageLoader::UncompressPackage(MEPackage& Package, MEFileArchive& Archive) {
	auto newArchive = std::make_unique<MEFileArchive>();

	// Verify

	auto& chunks = Package.Header.ChunkInfo.Array();

	if (chunks.empty()) {
		throw MEException("No chunks to decompress");
	}

	if (chunks.back().CompressedOffset + chunks.back().CompressedSize != Archive.Length()) {
		throw MEException("Unknown data after last chunk: %s", chunks.back().DebugInfo().c_str());
	}

	for (dword i = 0; i != chunks.size(); ++i) {
		if (i > 0) {
			if (chunks[i - 1].CompressedOffset + chunks[i - 1].CompressedSize != chunks[i].CompressedOffset) {
				throw MEException("Chunk[%d] compressed data is not located after previous one: %s %s", chunks[i - 1].DebugInfo().c_str(), chunks[i].DebugInfo().c_str());
			}
			if (chunks[i - 1].CompressedOffset >= chunks[i].CompressedOffset) {
				throw MEException("Chunk[%d] compressed offset is not increasing: %s %s", chunks[i - 1].DebugInfo().c_str(), chunks[i].DebugInfo().c_str());
			}

			if (chunks[i - 1].UncompressedOffset + chunks[i - 1].UncompressedSize != chunks[i].UncompressedOffset) {
				throw MEException("Chunk[%d] uncompressed data is not located after previous one: %s %s", chunks[i - 1].DebugInfo().c_str(), chunks[i].DebugInfo().c_str());
			}
			if (chunks[i - 1].UncompressedOffset >= chunks[i].UncompressedOffset) {
				throw MEException("Chunk[%d] uncompressed offset is not increasing: %s %s", chunks[i - 1].DebugInfo().c_str(), chunks[i].DebugInfo().c_str());
			}
		}
	}

	const dword totalUncompressedSize = chunks.back().UncompressedOffset + chunks.back().UncompressedSize;

	const dword maxSize = 1024 * 1024 * 1024; // 1GB
	if (totalUncompressedSize > maxSize) {
		throw MEException("Package too big to decompress: %d", totalUncompressedSize);
	}

	MEFileArchive& compressed = Archive;
	MEFileArchive& uncompressed = *newArchive;
	uncompressed.InitSize(totalUncompressedSize);

	compressed.Seek(0);
	uncompressed.Seek(0);
	//compressed.Serialize(uncompressed.GetDataPtr(), chunks.front().CompressedOffset);


	for (auto& chunkInfo : Package.Header.ChunkInfo.Array()) {
		uncompressed.Seek(chunkInfo.UncompressedOffset);
		compressed.Seek(chunkInfo.CompressedOffset);
		FCompressedChunkHeader chunkHeader;
		compressed << chunkHeader;
		Package.ChunkHeaders.push_back(chunkHeader);

		for (auto& block : chunkHeader.Blocks) {
			MECompression::UncompressMemory((MECompressionFlags)Package.Header.CompressionFlags,
				uncompressed.GetDataPtr(), block.UncompressedSize,
				compressed.GetDataPtr(), block.CompressedSize);

			compressed.Seek(block.CompressedSize, SeekMode::FromCurrent);
			uncompressed.Seek(block.UncompressedSize, SeekMode::FromCurrent);
		}
	}

	return newArchive;
}
