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
class MEFileArchive: public MEArchive
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
	bool bDecompressed;
	fs::path Path;

public:
	MEFileArchive(dword maxsize = 0x40000000)
		: Offset(0)
		, Size(0)
		, MaxSize(maxsize)
		, GuardMin(0)
		, GuardMax(0)
		, ByteInfo(BI_None)
		, Guards(1, MEFileGuard(0, 0))
		, bOpened(false)
		, bDecompressed(false)
	{
		// Guard 0 is 0,0
		// Guard 1 is 0,MaxSize
	}


	virtual ~MEFileArchive()
	{
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

	void ReadPath(fs::path path) {
		SetPath(path);

		auto file = std::ifstream(path.c_str(), std::ios::binary | std::ios::in);
		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		file.ignore(std::numeric_limits<std::streamsize>::max());
		auto size = (dword)file.gcount();
		file.clear();   //  Since ignore will have set eof.
		file.seekg(0, std::ios_base::beg);

		InitSize(size);

		file.read((char*)(&Data UP_AT(0)), Size);
	}

public:
	virtual void Serialize(void* buffer, dword count) override
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

	virtual void Seek(dword offset, SeekMode mode = SeekMode::FromStart) override
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

	virtual dword Tell() const override { return Offset; }
	virtual dword Length() const override { return Size; }

	virtual byte* GetDataPtr() override { return Data.empty() ? NULL : &Data UP_AT(Tell()); }

public:
	virtual bool			IsLoading() const override { return true; }
	virtual bool			IsSaving() const override { return false; }
	virtual bool			IsOpened() const override { return bOpened; }
	virtual bool			IsDecompressed() const override { return bDecompressed; }
	virtual void			SetDecompressed(bool bFlag) override { bDecompressed = bFlag; }

public:
	virtual void PushGuard(dword from, dword to) override
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

	virtual void PopGuard() override
	{
		Guards.pop_back();
		GuardMin = Guards.back().From;
		GuardMax = Guards.back().To;
	}

	virtual MEFileGuard GetGuard() const override
	{
		return Guards.back();
	}

public:
	virtual EByteInfo	GetByteInfo() const override { return ByteInfo; }
	virtual void		SetByteInfo(EByteInfo d) override { ByteInfo = d; }

	virtual void			SetPath(fs::path path) { Path = path; }
	virtual fs::path		GetPath() { return Path; }
	virtual std::string		GetName() { return Path.filename().string(); }

public:
	virtual std::string DebugInfo() const override;
	virtual void DumpByteInfo() const override;
};

