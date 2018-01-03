#pragma once


#include <fstream>
#include <vector>
#include <experimental/filesystem>

#include "MEBasicTypes.h"
#include "MEArchive.h"
#include "MECompressedChunkInfo.h"

namespace fs = std::experimental::filesystem;


// ============================================================================
// MEFile
// ============================================================================
class MEFileBuffer
{
protected:
	dword Offset;
	dword Size;
	dword MaxSize;
	dword GuardMin;
	dword GuardMax;
	EByteInfo ByteInfo;
	std::vector<byte> Data;
	std::vector<byte> Markers;
	std::vector<MEFileGuard> Guards;
	bool bOpened;

public:
	MEFileBuffer(dword maxsize = 0x40000000)
		: Offset(0)
		, Size(0)
		, MaxSize(maxsize)
		, GuardMin(0)
		, GuardMax(0)
		, ByteInfo(BI_None)
		, Guards(1, MEFileGuard(0, 0))
		, bOpened(false)
	{
		// Guard 0 is 0,0
		// Guard 1 is 0,MaxSize
	}

	~MEFileBuffer()
	{
	}


public:
	void Seek(dword offset, SeekMode mode = SeekMode::FromStart)
	{
		if (mode == SeekMode::FromStart)		Offset = offset;
		else if (mode == SeekMode::FromCurrent)	Offset += offset;
		else if (mode == SeekMode::FromEnd)		Offset = static_cast<dword>(Size) - offset;

		if (Offset < 0 || Offset > Size)
		{
			throw MEException("Invalid seek <0x%.8x> outside valid range <0x%.8x 0x%.8x>"
				, static_cast<dword>(Offset)
				, static_cast<dword>(0)
				, static_cast<dword>(Size)
			);
		}
	}

	dword Tell() const { return Offset; }
	dword Length() const { return Size; }

	byte* GetDataPtr() { return Data.empty() ? NULL : &Data UP_AT(0); }

public:
	bool IsOpened() const { return bOpened; }

public:
	void PushGuard(dword from, dword to)
	{
		if (from >= 0 && from < MaxSize && to >= 0 && to <= MaxSize)
		{
			Guards.push_back(MEFileGuard(from, to));
			GuardMin = from;
			GuardMax = to;
		}
		else
		{
			throw MEException("File guard <0x%.8x 0x%.8x> outside valid range <0x%.8x 0x%.8x>"
				, static_cast<dword>(from)
				, static_cast<dword>(to)
				, static_cast<dword>(0)
				, static_cast<dword>(MaxSize)
			);
		}
	}

	void PopGuard()
	{
		Guards.pop_back();
		GuardMin = Guards.back().From;
		GuardMax = Guards.back().To;
	}

	MEFileGuard GetGuard() const
	{
		return Guards.back();
	}

public:
	EByteInfo	GetByteInfo() const { return ByteInfo; }
	void		SetByteInfo(EByteInfo d) { ByteInfo = d; }

public:
	void DumpByteInfo();
};


// ============================================================================
// MEFileReadBuffer
// ============================================================================
class MEFileReadBuffer : public MEFileBuffer
{
public:
	MEFileReadBuffer(dword maxsize = 0x40000000)
		: MEFileBuffer(maxsize)
	{
	}

	~MEFileReadBuffer()
	{
	}

	void Init(std::fstream& file)
	{
		//UP_TIMER(t);

		file.ignore(std::numeric_limits<std::streamsize>::max());
		dword size = static_cast<dword>(file.gcount());
		file.clear();   //  Since ignore will have set eof.
		file.seekg(0, std::ios_base::beg);

		InitSize(size);

		file.read((char*)(&Data UP_AT(0)), Size);

		//UP_TIMER_LOGF(t,0);
	}


	void InitSize(dword size)
	{
		if (!bOpened)
			bOpened = true;
		else
			throw MEException("MEFileBuffer already opened");

		Size = size;
		if (Size > MaxSize)
			throw MEException("Excessive file size: %d", Size);

		MaxSize = Size;

		Data.reserve(Size);
		Data.resize(Size);

		Markers.reserve(Size);
		Markers.resize(Size);

		PushGuard(0, MaxSize);

		memset(&Markers UP_AT(0), 0, Size);
	}

public:
	void Read(void* buffer, dword count)
	{
		if (Offset >= GuardMin && Offset + count <= GuardMax)
		{
			// Mark byte as read
			memset(&Markers UP_AT(Offset), static_cast<byte>(ByteInfo), count);

			// Read
			memcpy(buffer, &Data UP_AT(Offset), count);
			Offset += count;
		}
		else
		{
			throw MEException("File read <0x%.8x 0x%.8x> outside guarded range <0x%.8x 0x%.8x>"
				, static_cast<dword>(Offset)
				, static_cast<dword>(Offset + count)
				, static_cast<dword>(GuardMin)
				, static_cast<dword>(GuardMax)
			);
		}
	}
};


// ============================================================================
// MEFile
// ============================================================================
class MEFile : public MEArchive
{
protected:
	fs::path Path;
	std::fstream Stream;

public:
	explicit MEFile(const fs::path& path);
	virtual ~MEFile();

public:
	virtual std::string		DebugInfo();
	virtual byte*			GetDataPtr() = 0;

public:
	virtual std::fstream&	GetStream() { return Stream; }
	virtual fs::path		GetPath() { return Path; }
	virtual std::string		GetName() { return Path.filename().string(); }
};


// ============================================================================
// MEFileReader
// ============================================================================
class MEFileReader : public MEFile
{
protected:
	MEFileReadBuffer	Buf;

public:
	explicit MEFileReader(const fs::path& path);

public:
	virtual void			Serialize(void* buffer, dword count) { Buf.Read(buffer, count); }
	virtual byte*			GetDataPtr() { return Buf.GetDataPtr(); }
	virtual void			DumpByteInfo();

public:
	virtual void			Seek(dword pos, SeekMode from = SeekMode::FromStart) { Buf.Seek(pos, from); }
	virtual void			SeekEnd(dword pos = 0) { Buf.Seek(pos, SeekMode::FromEnd); }
	virtual dword			Tell() { return Buf.Tell(); }
	virtual dword			Length() { return Buf.Length(); }

public:
	virtual bool			IsOpened() { return Buf.IsOpened(); }
	virtual bool			IsLoading() { return true; }
	virtual bool			IsSaving() { return false; }

public:
	virtual void			PushGuard(dword from, dword to) { Buf.PushGuard(from, to); }
	virtual void			PopGuard() { Buf.PopGuard(); }
	virtual MEFileGuard		GetGuard() { return Buf.GetGuard(); }

public:
	virtual void			SetByteInfo(EByteInfo info) { Buf.SetByteInfo(info); }
	virtual EByteInfo		GetByteInfo() { return Buf.GetByteInfo(); }

public:
	virtual void			Decompress(std::vector<MECompressedChunkInfo>& chunks, MECompressionFlags Flags);
};