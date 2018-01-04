#include "stdafx.h"
#include "MECompression.h"
#include "minilzo.h"


MECompression::MECompression()
{
}


MECompression::~MECompression()
{
}

bool MECompression::UncompressMemory(MECompressionFlags Flags, void* UncompressedBuffer, int32 UncompressedSize, const void* CompressedBuffer, int32 CompressedSize) {
	switch (Flags) {
	case MECompressionFlags::None:
		break;
	case MECompressionFlags::ZLIB:
		break;
	case MECompressionFlags::LZO: {
		lzo_uint uncompressedActualSize = UncompressedSize;
		auto result = lzo1x_decompress_safe((const unsigned char*)CompressedBuffer, CompressedSize, (unsigned char*)UncompressedBuffer, &uncompressedActualSize, nullptr);
		if (LZO_E_OK != result) {
			throw MEException("lzo1x_decompress_safe unexpected result %d", (int)result);
		}
		if (uncompressedActualSize != UncompressedSize) {
			throw MEException("lzo1x_decompress_safe expected %d bytes, got %d", UncompressedSize, uncompressedActualSize);
		}
		return true;
	}
	case MECompressionFlags::LZX:
		break;
	}
	throw MEException("Unsupported compression flag: %d", (int)Flags);
}
