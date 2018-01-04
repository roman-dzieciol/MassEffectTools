
#include "stdafx.h"
#include "MEFile.h"
#include "MECompression.h"
#include <ios>
#include <algorithm>

// ============================================================================
//	MEFileBuffer
// ============================================================================



// ============================================================================
//	MEFileArchive
// ============================================================================
std::string MEFileArchive::DebugInfo() const
{
	//wxString S;
	//S += wxString::Format(wxT(" N:<%s>"), PF_STR(FileName.GetName()));
	//S += wxString::Format(wxT(" SP:<0x%.8x 0x%.8x>"), static_cast<dword>(Length()), static_cast<dword>(Tell()));
	//S += wxString::Format(wxT("GR:<0x%.8x-0x%.8x>")
	//	, static_cast<dword>(GetGuard().From)
	//	, static_cast<dword>(GetGuard().To)
	//);
	//return S;
	return "";
}

void MEFileArchive::DumpByteInfo() const
{/*
 //wxLogMessage( wxT("ByteInfo:") );

 //if( !Markers )
 //	return;

 if (Data.size() > 0)
 {
 int from = 0;
 EByteInfo lastinfo = static_cast<EByteInfo>(Markers[0]);

 for (dword i = 0; i != Data.size(); ++i)
 {
 if (Markers[i] != lastinfo)
 {
 wxLogMessage(wxString::Format(wxT("<0x%.8x 0x%.8x> %s")
 , static_cast<dword>(from)
 , static_cast<dword>(i - 1)
 , PF_STR(upGetByteInfoName(lastinfo))
 ));
 lastinfo = static_cast<EByteInfo>(Markers[i]);
 from = i;
 }
 }

 wxLogMessage(wxString::Format(wxT("<0x%.8x 0x%.8x> %s")
 , static_cast<dword>(from)
 , static_cast<dword>(Data.size() - 1)
 , PF_STR(upGetByteInfoName(lastinfo))
 ));
 }

 wxLogMessage(wxString::Format(wxT("<0x%.8x> EOF")
 , static_cast<dword>(Size)
 ));*/
}

/*
void MEFileReader::Decompress(const std::vector<MECompressedChunkInfo>& chunks, MECompressionFlags flags)
{

	// Verify

	if (chunks.empty()) {
		throw MEException("No chunks to decompress");
	}

	if (chunks.back().CompressedOffset + chunks.back().CompressedSize != Length()) {
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

	MEFileReadBuffer& compressed = Buf;
	MEFileReadBuffer uncompressed;
	uncompressed.InitSize(totalUncompressedSize);

	compressed.Seek(0);
	compressed.Read(uncompressed.GetDataPtr(), chunks.front().CompressedOffset);

	dword uncompressedOffset = chunks.back().UncompressedOffset;
	for (dword i = 0; i != chunks.size(); ++i) {
		MECompression::UncompressMemory(flags,
			uncompressed.GetDataPtr() + chunks[i].UncompressedOffset, chunks[i].UncompressedSize,
			compressed.GetDataPtr() + chunks[i].CompressedOffset, chunks[i].CompressedSize);
	}

	Buf = uncompressed;
}
*/