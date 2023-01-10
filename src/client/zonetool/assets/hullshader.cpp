#include <std_include.hpp>
#include "hullshader.hpp"

namespace zonetool
{
	MaterialHullShader* IHullShader::parse(const std::string& name, ZoneMemory* mem)
	{
		const auto path = "techsets\\" + name + ".hullshader";

		assetmanager::reader read(mem);
		if (!read.open(path))
		{
			return nullptr;
		}

		//ZONETOOL_INFO("Parsing hullshader \"%s\"...", name.data());

		auto* asset = read.read_single<MaterialHullShader>();
		asset->name = read.read_string();
		asset->prog.loadDef.program = read.read_array<unsigned char>();
		read.close();

		return asset;
	}

	void IHullShader::init(const std::string& name, ZoneMemory* mem)
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
			this->asset_ = DB_FindXAssetHeader_Safe(XAssetType(this->type()), this->name().data()).hullShader;

			if (DB_IsXAssetDefault(XAssetType(this->type()), this->name().data()))
			{
				ZONETOOL_FATAL("hullshader \"%s\" not found.", name.data());
			}
		}
	}

	void IHullShader::prepare(ZoneBuffer* buf, ZoneMemory* mem)
	{
	}

	void IHullShader::load_depending(IZone* zone)
	{
	}

	std::string IHullShader::name()
	{
		return this->name_;
	}

	std::int32_t IHullShader::type()
	{
		return ASSET_TYPE_HULLSHADER;
	}

	void IHullShader::write(IZone* zone, ZoneBuffer* buf)
	{
		auto data = this->asset_;
		auto dest = buf->write(data);

		buf->push_stream(3);
		dest->name = buf->write_str(this->name());

		buf->push_stream(0);
		if (data->prog.loadDef.program)
		{
			dest->prog.loadDef.program = buf->write_s(3, data->prog.loadDef.program, data->prog.loadDef.programSize);
		}
		buf->pop_stream();

		buf->pop_stream();
	}

	void IHullShader::dump(MaterialHullShader* h2_asset)
	{
		utils::memory::allocator allocator;
		const auto asset = allocator.allocate<MaterialHullShader>();
		std::memcpy(asset, h2_asset, sizeof(MaterialHullShader));
		asset->name = allocator.duplicate_string(add_postfix(asset->name));
		const auto path = "techsets\\"s + asset->name + ".hullshader"s;

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