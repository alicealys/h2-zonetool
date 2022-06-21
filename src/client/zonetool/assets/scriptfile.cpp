#include <std_include.hpp>
#include "scriptfile.hpp"
#include "zlib.h"

namespace zonetool
{
	ScriptFile* IScriptFile::parse(const std::string& name, ZoneMemory* mem)
	{
		auto file_1 = filesystem::file(utils::string::va("%s.cgsc", name.data()));
		auto file_2 = filesystem::file(utils::string::va("%s.cgsc.stack", name.data()));
		if (file_1.exists() && file_2.exists())
		{
			auto* scriptfile = mem->Alloc<ScriptFile>();
			scriptfile->name = mem->StrDup(name);

			ZONETOOL_INFO("Parsing scriptfile \"%s\"...", name.data());

			// parse bytecode
			file_1.open("rb");
			if (file_1.get_fp())
			{
				ZONETOOL_INFO("Parsing scriptfile bytecode for script \"%s\"...", name.data());

				auto size = file_1.size();
				auto data = file_1.read_bytes(size);

				scriptfile->bytecode = mem->Alloc<char>(size);
				scriptfile->bytecodeLen = static_cast<int>(size);
				memcpy(scriptfile->bytecode, &data[0], size);

				file_1.close();
			}

			// parse stack
			file_2.open("rb");
			if (file_2.get_fp())
			{
				ZONETOOL_INFO("Parsing scriptfile heap for script \"%s\"...", name.data());

				auto size = file_2.size();
				auto data = file_2.read_bytes(size);

				ZoneBuffer buf(data);
				auto compressed = buf.compress_zlib();

				scriptfile->len = static_cast<int>(size);
				scriptfile->compressedLen = static_cast<int>(compressed.size());
				scriptfile->buffer = mem->Alloc<char>(compressed.size());
				memcpy(
					const_cast<char*>(scriptfile->buffer),
					compressed.data(),
					compressed.size());

				file_2.close();
			}

			return scriptfile;
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
		auto file_1 = filesystem::file(utils::string::va("%s.cgsc", asset->name));
		auto file_2 = filesystem::file(utils::string::va("%s.cgsc.stack", asset->name));

		file_1.open("wb");
		file_2.open("wb");

		if (asset->bytecode)
		{
			file_1.write(asset->bytecode, asset->bytecodeLen, 1);
		}

		if (asset->buffer)
		{
			std::vector<std::uint8_t> uncompressed;
			uncompressed.resize(asset->len);

			uncompress(uncompressed.data(), (uLongf*)&asset->len, (Bytef*)asset->buffer, asset->compressedLen);

			file_2.write(uncompressed.data(), uncompressed.size(), 1);
		}

		file_1.close();
		file_2.close();
	}
}