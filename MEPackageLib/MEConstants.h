#pragma once

#include "MEBasicTypes.h"

namespace MEConst
{
	const dword signature = 0x9E2A83C1;
	const word packageVersion = 0x01EB;
	const word licenseMode = 0x03F0;

}


enum class MECompressionFlags {
	None = 0x0,
	ZLIB = 0x1,
	LZO = 0x2,
	LZX = 0x4
};
