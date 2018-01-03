#pragma once

// ============================================================================
// EByteInfo
// ============================================================================
enum EByteInfo
{
	BI_None = 0x00,
	BI_Header = 0x01,
	BI_NameTable = 0x02,
	BI_ImportTable = 0x04,
	BI_ExportTable = 0x08,
	BI_GenerationTable = 0x10,
	BI_Object = 0x20,
};

inline std::string upGetByteInfoName(EByteInfo info)
{
	switch (info)
	{
	case BI_None:				return ("BI_None");
	case BI_Header:				return ("BI_Header");
	case BI_NameTable:			return ("BI_NameTable");
	case BI_ImportTable:		return ("BI_ImportTable");
	case BI_ExportTable:		return ("BI_ExportTable");
	case BI_GenerationTable:	return ("BI_GenerationTable");
	case BI_Object:				return ("BI_Object");
	default:					return ("BI_UNKNOWN");
	}
}


// ============================================================================
// MEFileGuard
// ============================================================================
struct MEFileGuard
{
	dword	From;
	dword	To;

	MEFileGuard(dword from, dword to) : From(from), To(to)
	{
	}
};

enum class SeekMode {
	FromStart = 0,
	FromEnd,
	FromCurrent
};

// ============================================================================
// MEArchive
// ============================================================================
class MEArchive
{
public:
	virtual ~MEArchive() = 0;


public:
	virtual void			Serialize(void* buffer, dword count) = 0;

public:
	virtual void			Seek(dword pos, SeekMode from = SeekMode::FromStart) = 0;
	virtual void			SeekEnd(dword pos = 0) = 0;
	virtual dword			Tell() = 0;
	virtual dword			Length() = 0;

public:
	virtual bool			IsOpened() = 0;
	virtual bool			IsLoading() = 0;
	virtual bool			IsSaving() = 0;

public:
	virtual void			PushGuard(dword from, dword to) = 0;
	virtual void			PopGuard() = 0;
	virtual MEFileGuard		GetGuard() = 0;

public:
	virtual void			SetByteInfo(EByteInfo info) = 0;
	virtual EByteInfo		GetByteInfo() = 0;

public:
	virtual std::string		DebugInfo() = 0;
	virtual void			DumpByteInfo() = 0;

public:
	friend void operator << (MEArchive& A, qword& D) { A.Serialize(&D, sizeof(qword)); /*wxUINT64_SWAP_ON_?E(D);*/ }
	friend void operator << (MEArchive& A, dword& D) { A.Serialize(&D, sizeof(dword)); /*wxUINT32_SWAP_ON_?E(D);*/ }
	friend void operator << (MEArchive& A, word& D) { A.Serialize(&D, sizeof(word)); /*wxUINT16_SWAP_ON_?E(D);*/ }
	friend void operator << (MEArchive& A, byte& D) { A.Serialize(&D, sizeof(byte)); }
	friend void operator << (MEArchive& A, int64& D) { A.Serialize(&D, sizeof(int64)); /*wxINT64_SWAP_ON_?E(D);*/ }
	friend void operator << (MEArchive& A, int32& D) { A.Serialize(&D, sizeof(int32)); /*wxINT32_SWAP_ON_?E(D);*/ }
	friend void operator << (MEArchive& A, int16& D) { A.Serialize(&D, sizeof(int16)); /*wxINT16_SWAP_ON_?E(D);*/ }
	friend void operator << (MEArchive& A, int8& D) { A.Serialize(&D, sizeof(int8)); }
	friend void operator << (MEArchive& A, char& D) { A.Serialize(&D, sizeof(char)); }
	friend void operator << (MEArchive& A, wchar_t& D) { A.Serialize(&D, sizeof(wchar_t)); }
	friend void operator << (MEArchive& A, float& D) { A.Serialize(&D, sizeof(float)); /*wxINT32_SWAP_ON_?E(D);*/ }

public:
	friend MEArchive& operator << (MEArchive& A, EByteInfo D) { A.SetByteInfo(D); return A; }
};


// ============================================================================
// MEOffsetGuard
// ============================================================================
class MEOffsetGuard
{
private:
	MEArchive& A;

public:
	MEOffsetGuard(MEArchive& a, dword from, dword to) : A(a)
	{
		A.PushGuard(from, to);
	}

	~MEOffsetGuard()
	{
		A.PopGuard();
	}
};

#define UP_OFFSET_GUARD(name,arc,from,to) MEOffsetGuard offsetguard_##name(arc,from,to);



// ============================================================================
// MEByteMarker
// ============================================================================
class MEByteMarker
{
private:
	MEArchive& A;

public:
	MEByteMarker(MEArchive& a, dword offset, EByteInfo byteinfo) : A(a)
	{
		A.Seek(offset);
		A << byteinfo;
	}

	~MEByteMarker()
	{
		A << BI_None;
	}
};

#define UP_BYTE_MARKER(name,arc,offset,byteinfo) MEByteMarker bytemarker_##name(arc,offset,byteinfo);

