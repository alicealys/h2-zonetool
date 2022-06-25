#include <std_include.hpp>
#include "scriptfile.hpp"
#include "zlib.h"

namespace zonetool
{
	ScriptFile* IScriptFile::parse(const std::string& name, ZoneMemory* mem)
	{
		auto file = filesystem::file(utils::string::va("%s.gscbin", name.data()));
		file.open("rb");
		auto* fp = file.get_fp();

		if (fp)
		{
			auto* asset = mem->Alloc<ScriptFile>();

			std::string m_name;
			file.read_string(&m_name);
			asset->name = mem->StrDup(m_name);

			file.read(&asset->compressedLen, sizeof(asset->compressedLen), 1);
			file.read(&asset->len, sizeof(asset->len), 1);
			file.read(&asset->bytecodeLen, sizeof(asset->bytecodeLen), 1);

			asset->buffer = mem->Alloc<char>(asset->compressedLen);
			asset->bytecode = mem->Alloc<char>(asset->bytecodeLen);
			file.read(const_cast<char*>(asset->buffer), sizeof(char), asset->compressedLen);
			file.read(const_cast<char*>(asset->bytecode), sizeof(char), asset->bytecodeLen);

			return asset;
		}

		return nullptr;
	}

	void IScriptFile::init(const std::string& name, ZoneMemory* mem)
	{
		this->name_ = name;
		this->asset_ = this->parse(name, mem);

		if (!this->asset_)
		{
			this->asset_ = DB_FindXAssetHeader(XAssetType(this->type()), this->name_.data(), 1).scriptfile;
		}
	}

	void IScriptFile::prepare(ZoneBuffer* buf, ZoneMemory* mem)
	{
	}

	void IScriptFile::load_depending(IZone* zone)
	{
	}

	std::string IScriptFile::name()
	{
		return this->name_;
	}

	std::int32_t IScriptFile::type()
	{
		return ASSET_TYPE_SCRIPTFILE;
	}

	void IScriptFile::write(IZone* zone, ZoneBuffer* buf)
	{
		auto* data = this->asset_;
		auto* dest = buf->write<ScriptFile>(data);

		buf->push_stream(3);

		dest->name = buf->write_str(this->name());

		buf->push_stream(6);

		if (data->buffer)
		{
			buf->write(data->buffer, data->compressedLen);
			ZoneBuffer::clear_pointer(&dest->buffer);
		}

		if (data->bytecode)
		{
			buf->write(data->bytecode, data->bytecodeLen);
			ZoneBuffer::clear_pointer(&dest->bytecode);
		}

		buf->pop_stream();

		buf->pop_stream();
	}

	void IScriptFile::dump(ScriptFile* asset)
	{
		auto file = filesystem::file(utils::string::va("%s.gscbin", asset->name));
		file.open("wb");
		auto* fp = file.get_fp();

		if (fp)
		{
			file.write_string(asset->name);
			file.write(&asset->compressedLen, sizeof(asset->compressedLen), 1);
			file.write(&asset->len, sizeof(asset->len), 1);
			file.write(&asset->bytecodeLen, sizeof(asset->bytecodeLen), 1);
			file.write(asset->buffer, asset->compressedLen, 1);
			file.write(asset->bytecode, asset->bytecodeLen , 1);

			file.close();
		}
	}
}