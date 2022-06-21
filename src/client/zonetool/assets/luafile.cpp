#include <std_include.hpp>
#include "luafile.hpp"

namespace zonetool
{
	LuaFile* ILuaFile::parse(const std::string& name, ZoneMemory* mem)
	{
		auto file = filesystem::file(name);

		if (file.exists())
		{
			ZONETOOL_INFO("Parsing luafile \"%s\"...", name.data());

			auto* luafile = mem->Alloc<LuaFile>();
			luafile->name = mem->StrDup(name);

			file.open("rb");
			if (file.get_fp())
			{
				const auto size = file.size();
				auto data = file.read_bytes(size);

				luafile->len = static_cast<int>(size);
				luafile->buffer = mem->Alloc<char>(luafile->len);
				memcpy(
					const_cast<char*>(luafile->buffer),
					data.data(),
					data.size());

				file.close();
			}

			return luafile;
		}

		return nullptr;
	}

	void ILuaFile::init(const std::string& name, ZoneMemory* mem)
	{
		this->name_ = name;
		this->asset_ = parse(name, mem);

		if (!this->asset_)
		{
			this->asset_ = DB_FindXAssetHeader_Safe(XAssetType(this->type()), this->name_.data()).luaFile;
		}
	}

	void ILuaFile::prepare(ZoneBuffer* buf, ZoneMemory* mem)
	{
	}

	void ILuaFile::load_depending(IZone* zone)
	{
	}

	std::string ILuaFile::name()
	{
		return this->name_;
	}

	std::int32_t ILuaFile::type()
	{
		return ASSET_TYPE_LUA_FILE;
	}

	void ILuaFile::write(IZone* zone, ZoneBuffer* buf)
	{
		auto* data = this->asset_;
		auto* dest = buf->write<LuaFile>(data);

		buf->push_stream(3);

		dest->name = buf->write_str(this->name());

		if (data->buffer)
		{
			buf->align(15);
			buf->write(data->buffer, data->len);
			ZoneBuffer::clear_pointer(&dest->buffer);
		}

		buf->pop_stream();
	}

	void ILuaFile::dump(LuaFile* asset)
	{
		auto f = filesystem::file(asset->name);
		f.open("wb");

		if (asset->len > 0)
		{
			f.write(asset->buffer, asset->len, 1);
		}

		f.close();
	}
}