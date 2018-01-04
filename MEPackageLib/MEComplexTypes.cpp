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
		char* ascii_str = new char[length];
		A.Serialize(ascii_str, length);
		D.Text = std::string(ascii_str, length);
		delete[]ascii_str;

		/*wxCharBuffer buffer(length);
		A.Serialize( buffer.data(), length );
		wxWCharBuffer wbuffer = wxConvLocal.cMB2WC(buffer);
		D.Text = wxString(wbuffer);*/
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

// ============================================================================
//  MEUNICODEZ
// ============================================================================
MEArchive& operator << (MEArchive& A, MEUNICODEZ& D)
{
	D.Text.clear();
	std::vector<char> chars;
	char c;
	do { A << c; chars.push_back(c); } while (c != 0);
	D.Text = std::string(&chars[0]);
	return A;
}


// ============================================================================
//  MEASCIIZ
// ============================================================================
MEArchive& operator << (MEArchive& A, MEASCIIZ& D)
{
	D.Text.clear();
	std::vector<char> chars;
	char c;
	do { A << c; chars.push_back(c); } while (c != 0);
	D.Text = std::string(&chars[0]);
	return A;
}
