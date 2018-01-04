#pragma once
#include <memory>

class MECompression
{
public:
	MECompression();
	~MECompression();

	static bool UncompressMemory(MECompressionFlags Flags, void* UncompressedBuffer, int32 UncompressedSize, const void* CompressedBuffer, int32 CompressedSize);
	


};

