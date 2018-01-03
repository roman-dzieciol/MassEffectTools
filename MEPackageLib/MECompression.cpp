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
	case MECompressionFlags::LZO:
		break;
	case MECompressionFlags::LZX:
		break;
	}
	throw MEException("Unsupported compression flag: %d", (int)Flags);
}
