#include <std_include.hpp>
#include "rawfile.hpp"

#include <zlib.h>

#define ZONETOOL_BRANDING "Compiled using H2 ZoneTool."

namespace zonetool
{
	RawFile* IRawFile::parse(const std::string& name, ZoneMemory* mem)
	{
		auto file = filesystem::file(name);
		file.open("rb");

		if (file.get_fp())
		{
			ZONETOOL_INFO("Parsing rawfile \"%s\"...", name.data());

			const auto size = file.size();
			auto data = file.read_bytes(size);

			auto* rawfile = mem->Alloc<RawFile>();
			rawfile->name = mem->StrDup(name);
			rawfile->len = static_cast<int>(size);

			ZoneBuffer buf(data);
			auto compressed_data = buf.compress_zlib();

			// Only save the compressed buffer if we gained space
			if (compressed_data.size() < size)
			{
				rawfile->compressedLen = static_cast<int>(compressed_data.size());
				rawfile->buffer = mem->Alloc<char>(compressed_data.size());
				std::memcpy(const_cast<char*>(rawfile->buffer), compressed_data.data(), compressed_data.size());
			}
			else
			{
				rawfile->compressedLen = 0;	
				rawfile->buffer = mem->Alloc<char>(size + 1);
				std::memcpy(const_cast<char*>(rawfile->buffer), data.data(), size);
			}

			file.close();

			return rawfile;
		}

		return nullptr;
	}

	void IRawFile::init(const std::string& name, ZoneMemory* mem)
	{
		this->name_ = name;

		if (this->referenced())
		{
			this->asset_ = mem->Alloc<typename std::remove_reference<decltype(*this->asset_)>::type>();
			this->asset_->name = mem->StrDup(name);
			return;
		}

		this->asset_ = parse(name, mem);
		if (name == filesystem::get_fastfile())
		{
			this->asset_ = mem->Alloc<RawFile>();
			this->asset_->name = mem->StrDup(name);
			this->asset_->buffer = mem->StrDup(ZONETOOL_BRANDING);
			this->asset_->len = static_cast<int>(std::strlen(this->asset_->buffer));
			this->asset_->compressedLen = 0;

		}
		else if (!this->asset_)
		{
			this->asset_ = DB_FindXAssetHeader_Safe(XAssetType(this->type()), this->name_.data()).rawfile;
		}
	}

	void IRawFile::prepare(ZoneBuffer* buf, ZoneMemory* mem)
	{
	}

	void IRawFile::load_depending(IZone* zone)
	{
	}

	std::string IRawFile::name()
	{
		return this->name_;
	}

	std::int32_t IRawFile::type()
	{
		return ASSET_TYPE_RAWFILE;
	}

	void IRawFile::write(IZone* zone, ZoneBuffer* buf)
	{
		auto* data = this->asset_;
		auto* dest = buf->write<RawFile>(data);

		buf->push_stream(3);

		dest->name = buf->write_str(this->name());

		if (data->buffer)
		{
			buf->align(0);
			buf->write(data->buffer, data->compressedLen ? data->compressedLen : data->len + 1);
			ZoneBuffer::clear_pointer(&dest->buffer);
		}

		buf->pop_stream();
	}

	void IRawFile::dump(RawFile* asset)
	{
		auto file = filesystem::file(asset->name);
		file.open("wb");

		if (asset->compressedLen > 0)
		{
			std::vector<std::uint8_t> uncompressed;
			uncompressed.resize(asset->len);

			uncompress(uncompressed.data(), (uLongf*)&asset->len, (Bytef*)asset->buffer, asset->compressedLen);

			file.write(uncompressed.data(), uncompressed.size(), 1);
		}
		else if (asset->len > 0)
		{
			file.write(asset->buffer, asset->len, 1);
		}

		file.close();
	}
}
