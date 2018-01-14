#include "stdafx.h"
#include "MEComplexTypes.h"

// ============================================================================
//  MEString
// ============================================================================
MEArchive& operator << (MEArchive& A, MEString& D)
{
	dword length;
	A << length;

	if (length > 0)
	{
		if (length > 1000000) {
			throw MEException("MEString length too big: %d, %s", length, A.DebugInfo().c_str());
		}
		std::vector<char> chars(length, 0);
		A.Serialize(&chars[0], length);
		if (length > 1 && chars[length - 1] == 0) {
			length -= 1;
			chars.resize(length);
		}
		for (char& c : chars) {
			c = MESanitizeAscii(c);
		}

		D.Text = std::string(&chars[0], length);
	}
	return A;
}


// ============================================================================
//  MEGUID
// ============================================================================
MEArchive& operator << (MEArchive& A, MEGUID& D)
{
	A << D.Data[0];
	A << D.Data[1];
	A << D.Data[2];
	A << D.Data[3];
	return A;
}

std::string MEGUID::String() const {
	return MEFormat("{%0.8x-%0.8x-%0.8x-%0.8x}", Data[0], Data[1], Data[2], Data[3]);
}

// ============================================================================
//  MEUNICODEZ
// ============================================================================
MEArchive& operator << (MEArchive& A, MEUNICODEZ& D)
{
	throw MENotImplemented();
	//D.Text.clear();
	//std::vector<char> chars;
	//char c;
	//do { 
	//	A << c;
	//	if (c != 0) {
	//		c = MESanitizeAscii(c);
	//	}
	//	chars.push_back(c); 
	//} while (c != 0);
	//D.Text = std::string(&chars[0]);
	//return A;
}


// ============================================================================
//  MEASCIIZ
// ============================================================================
MEArchive& operator << (MEArchive& A, MEASCIIZ& D)
{
	D.Text.clear();
	std::vector<char> chars;
	char c;
	do { 
		A << c; 
		if (c != 0) {
			c = MESanitizeAscii(c);
		}
		chars.push_back(c); 
	} while (c != 0);
	D.Text = std::string(&chars[0]);
	return A;
}
