#include <std_include.hpp>
#include "vertexshader.hpp"
#include "techset.hpp"

#include <utils/compression.hpp>

namespace zonetool
{
	MaterialVertexShader* IVertexShader::parse(const std::string& name, ZoneMemory* mem)
	{
		const auto path = "techsets\\" + name + ".vertexshader";

		assetmanager::reader read(mem);
		if (!read.open(path))
		{
			return nullptr;
		}

		//ZONETOOL_INFO("Parsing vertexshader \"%s\"...", name.data());

		auto* asset = read.read_single<MaterialVertexShader>();
		asset->name = read.read_string();
		asset->prog.loadDef.program = read.read_array<unsigned char>();
		read.close();

		return asset;
	}

	void IVertexShader::init(const std::string& name, ZoneMemory* mem)
	{
		this->name_ = name;

		if (this->referenced())
		{
			this->asset_ = mem->Alloc<typename std::remove_reference<decltype(*this->asset_)>::type>();
			this->asset_->name = mem->StrDup(name);
			return;
		}

		this->asset_ = this->parse(name, mem);
		if (!this->asset_)
		{
			this->asset_ = DB_FindXAssetHeader_Safe(XAssetType(this->type()), this->name().data()).vertexShader;

			if (DB_IsXAssetDefault(XAssetType(this->type()), this->name().data()))
			{
				ZONETOOL_FATAL("vertexshader \"%s\" not found.", name.data());
			}
		}
	}

	void IVertexShader::prepare(ZoneBuffer* buf, ZoneMemory* mem)
	{
	}

	void IVertexShader::load_depending(IZone* zone)
	{
	}

	std::string IVertexShader::name()
	{
		return this->name_;
	}

	std::int32_t IVertexShader::type()
	{
		return ASSET_TYPE_VERTEXSHADER;
	}

	void IVertexShader::write(IZone* zone, ZoneBuffer* buf)
	{
		auto data = this->asset_;
		auto dest = buf->write(data);

		buf->push_stream(3);

		dest->name = buf->write_str(this->name());

		if (data->prog.loadDef.program)
		{
			dest->prog.loadDef.program = buf->write_s(3, data->prog.loadDef.program, data->prog.loadDef.programSize);
		}

		buf->pop_stream();
	}

	void IVertexShader::dump(MaterialVertexShader* h2_asset)
	{
		utils::memory::allocator allocator;
		const auto asset = allocator.allocate<MaterialVertexShader>();
		std::memcpy(asset, h2_asset, sizeof(MaterialVertexShader));
		asset->name = allocator.duplicate_string(add_postfix(asset->name));
		const auto path = "techsets\\"s + asset->name + ".vertexshader"s;
		asset->prog.loadDef.program = 
			convert_shader(asset->prog.loadDef.program, asset->prog.loadDef.programSize, allocator);
		asset->prog.loadDef.microCodeCrc = shader::crc32(asset->prog.loadDef.program, asset->prog.loadDef.programSize);

		assetmanager::dumper write;
		if (!write.open(path))
		{
			return;
		}

		write.dump_single(asset);
		write.dump_string(asset->name);
		write.dump_array(asset->prog.loadDef.program, asset->prog.loadDef.programSize);
		write.close();
	}
}