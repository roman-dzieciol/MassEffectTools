#include "stdafx.h"
#include "MEPackageLoader.h"
#include <iostream>
#include "MEExporterSQL.h"
#include "MEFLinker.h"
#include "MEUObject.h"

MEPackageLoader::MEPackageLoader()
{
}


MEPackageLoader::~MEPackageLoader()
{
}

void MEPackageLoader::LoadObjects(MEFileArchive& A, MEPackage& D) {

	for (auto& exportItem : D.ExportTable.Items) {
		try
		{
			A.Seek(exportItem.SerialOffset);
			UP_OFFSET_GUARD(object, A, exportItem.SerialOffset, exportItem.SerialOffset + exportItem.SerialSize);
			UP_BYTE_MARKER(object, A, A.Tell(), BI_Object);


			auto className = D.GetObjectName(exportItem.ClassObject);
			auto object = ObjectFactory.ConstructByClassName(className);
			if (object) {
				object->_TableIndex = exportItem.TableIndex;
				object->_Name = D.GetObjectName(MEObjectIndex::FromExportIndex(exportItem.TableIndex));
				object->Serialize(A);
				D.ExportObjects.push_back(std::move(object));
			}
			else {
				A.Serialize(nullptr, exportItem.SerialSize);
			}

			int readMismatch = A.Tell() - (exportItem.SerialOffset + exportItem.SerialSize);
			if (readMismatch != 0) {
				throw MEException("Mismatch reading object:%s index:0x%x offset:0x%x bytes:%d", className.c_str(), exportItem.TableIndex, exportItem.SerialOffset, readMismatch);
			}
		}
		catch (const std::exception& e)
		{
			std::cerr << MEFormat("Error reading object index:0x%x offset:0x%x", exportItem.TableIndex, exportItem.SerialOffset) << std::endl;
			std::cerr << "Exception: " << e.what() << std::endl;
		}
	}

	A.GetLinker()->LoadScripts(A);
}

void MEPackageLoader::DumpPackage(MEFileArchive& A, MEPackage& D, fs::path path) {


	// Dump byte info
	//auto byteInfo = A.DumpByteInfo();
	//std::cout << byteInfo << std::endl;


	// Dump SQL
	auto sqlPath = path;
	sqlPath.replace_extension(".sql");
	auto sqlStream = std::fstream(sqlPath.string(), std::ios::out | std::ios::trunc);
	auto sqlExporter = MEExporterSQL(sqlStream);
	sqlExporter.ExportPackage(D);

	//f.SetDecompressed(true);
	//f << pkg;
}

std::unique_ptr<MEPackage> MEPackageLoader::Load(fs::path path, MENativeFunctionTable* FunctionTable)
{
	MEFileArchive f;
	f.ReadPath(path);
	auto pkg = std::make_unique<MEPackage>();
	auto linker = MEFLinker(pkg.get(), FunctionTable);
	f.SetLinker(&linker);
	f << *pkg;

	if (pkg->Header.CompressionFlags != (dword)MECompressionFlags::None && !f.IsDecompressed()) {
		//f.Decompress(pkg.Header.ChunkInfo.Array(), static_cast<MECompressionFlags>(pkg.Header.CompressionFlags));
		auto A = UncompressPackage(*pkg, f);
		A->Seek(0);


		auto inflatedPath = path;
		inflatedPath.replace_extension(".inflated");
		auto inflatedStream = std::fstream(inflatedPath.string(), std::ios::binary | std::ios::out | std::ios::trunc);
		inflatedStream.write((const char*)A->GetDataPtr(), A->Length());

		A->Seek(0);
		auto upkg = std::make_unique<MEPackage>();

		auto ulinker = MEFLinker(upkg.get(), FunctionTable);
		A->SetLinker(&ulinker);

		*A << *upkg;

		//DumpPackage(*A, upkg, path);
		LoadObjects(*A, *upkg);
		return upkg;
	}
	else {

		//DumpPackage(f, pkg, path);
		LoadObjects(f, *pkg);
		return pkg;
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
	compressed.Serialize(uncompressed.GetDataPtr(), chunks.front().UncompressedOffset);

	uncompressed.Seek(chunks.front().UncompressedOffset - sizeof(dword) * 4);
	memset(uncompressed.GetDataPtr(), 0, sizeof(dword) * 2);

	compressed.Seek(chunks.front().CompressedOffset - sizeof(dword) * 2);
	uncompressed.Seek(chunks.front().UncompressedOffset - sizeof(dword) * 2);
	compressed.Serialize(uncompressed.GetDataPtr(), sizeof(dword) * 2);

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
