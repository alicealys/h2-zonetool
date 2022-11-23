#include <std_include.hpp>
#include "techset.hpp"

#include "vertexshader.hpp"
#include "vertexdecl.hpp"
#include "hullshader.hpp"
#include "domainshader.hpp"
#include "pixelshader.hpp"

namespace zonetool
{
	std::unordered_map<std::string, std::uintptr_t> ITechset::vertexdecl_pointers;

	std::uintptr_t ITechset::get_vertexdecl_pointer(std::string vertexdecl)
	{
		if (vertexdecl_pointers.find(vertexdecl) != vertexdecl_pointers.end())
		{
			return vertexdecl_pointers[vertexdecl];
		}
		return 0;
	}

	void ITechset::add_vertexdecl_pointer(std::string name, std::uintptr_t pointer)
	{
		auto ptr = get_vertexdecl_pointer(name);
		if (!ptr)
		{
			vertexdecl_pointers[name] = pointer;
		}
	}

	MaterialTechnique* parse_technique(const std::string& name, ZoneMemory* mem, std::uint32_t index)
	{
		const auto path = "techsets\\" + name + ".technique";

		assetmanager::reader reader(mem);
		if (!reader.open(path))
		{
			ZONETOOL_FATAL("technique \"%s\" is missing.", name.data());
			return nullptr;
		}

		//ZONETOOL_INFO("Parsing technique \"%s\"...", name.data());

		const auto header = reader.read_single<MaterialTechniqueHeader>();
		const auto passes = reader.read_array<MaterialPass>();

		header->name = reader.read_string();

		const auto asset = mem->ManualAlloc<MaterialTechnique>(sizeof(MaterialTechniqueHeader) + (sizeof(MaterialPass) * header->passCount));
		memcpy(&asset->hdr, header, sizeof MaterialTechniqueHeader);
		memcpy(asset->passArray, passes, sizeof(MaterialPass) * header->passCount);

		for (unsigned short i = 0; i < header->passCount; i++)
		{
			if (asset->passArray[i].vertexShader)
			{
				asset->passArray[i].vertexShader = reader.read_asset<MaterialVertexShader>();
			}

			if (asset->passArray[i].vertexDecl)
			{
				asset->passArray[i].vertexDecl = reader.read_asset<MaterialVertexDeclaration>();
				asset->passArray[i].vertexDecl = IVertexDecl::parse(asset->passArray[i].vertexDecl->name, mem);
			}

			if (asset->passArray[i].hullShader)
			{
				asset->passArray[i].hullShader = reader.read_asset<MaterialHullShader>();
			}

			if (asset->passArray[i].domainShader)
			{
				asset->passArray[i].domainShader = reader.read_asset<MaterialDomainShader>();
			}

			if (asset->passArray[i].pixelShader)
			{
				asset->passArray[i].pixelShader = reader.read_asset<MaterialPixelShader>();
			}

			if (asset->passArray[i].args)
			{
				asset->passArray[i].args = reader.read_array<MaterialShaderArgument>();

				for (auto arg = 0; arg < asset->passArray[i].perObjArgCount + asset->passArray[i].perPrimArgCount + asset->passArray[i].stableArgCount; arg++)
				{
					if (asset->passArray[i].args[arg].type == 4)
					{
						asset->passArray[i].args[arg].u.literalConst = reader.read_array<float>();
					}
				}
			}
		}

		reader.close();

		return asset;
	}

	MaterialTechniqueSet* ITechset::parse(const std::string& name, ZoneMemory* mem)
	{
		const auto path = "techsets\\" + name + ".techset";

		assetmanager::reader reader(mem);
		if (!reader.open(path))
		{
			return nullptr;
		}

		ZONETOOL_INFO("Parsing techset \"%s\"...", name.data());

		const auto asset = reader.read_single<MaterialTechniqueSet>();
		asset->name = reader.read_string();

		for (auto i = 0u; i < TECHNIQUES_COUNT; i++)
		{
			if (asset->techniques[i])
			{
				asset->techniques[i] = parse_technique(reader.read_string(), mem, i);
			}
		}

		if (asset->techniques[0] && asset->techniques[0]->hdr.name == "textured_3d"s)
		{
			ZONETOOL_WARNING("techset \"%s\" is invalid!", name.data());
		}

		reader.close();

		return asset;
	}

	void ITechset::parse_constant_buffer_indexes(const std::string& techset, unsigned char* indexes, ZoneMemory* mem)
	{
		const auto path = "techsets\\constantbuffer\\"s + techset + ".cbi";
		auto file = filesystem::file(path);
		file.open("rb");
		auto fp = file.get_fp();

		if (fp)
		{
			fread(indexes, TECHNIQUES_COUNT, 1, fp);
			file.close();
			return;
		}

		ZONETOOL_FATAL("constantbufferindexes for techset \"%s\" are missing!", techset.data());
	}

	void ITechset::parse_constant_buffer_def_array(const std::string& techset, MaterialConstantBufferDef** def_ptr, unsigned char* count, ZoneMemory* mem)
	{
		const auto path = "techsets\\constantbuffer\\"s + techset + ".cbt";
		assetmanager::reader read(mem);
		if (!read.open(path))
		{
			(*def_ptr) = nullptr;
			return;
		}

		*count = static_cast<unsigned char>(read.read_int());
		auto def = read.read_array<MaterialConstantBufferDef>();
		for (int i = 0; i < *count; i++)
		{
			if (def[i].vsData)
			{
				def[i].vsData = read.read_array<unsigned char>();
			}
			if (def[i].hsData)
			{
				def[i].hsData = read.read_array<unsigned char>();
			}
			if (def[i].dsData)
			{
				def[i].dsData = read.read_array<unsigned char>();
			}
			if (def[i].psData)
			{
				def[i].psData = read.read_array<unsigned char>();
			}
			if (def[i].vsOffsetData)
			{
				def[i].vsOffsetData = read.read_array<unsigned short>();
			}
			if (def[i].hsOffsetData)
			{
				def[i].hsOffsetData = read.read_array<unsigned short>();
			}
			if (def[i].dsOffsetData)
			{
				def[i].dsOffsetData = read.read_array<unsigned short>();
			}
			if (def[i].psOffsetData)
			{
				def[i].psOffsetData = read.read_array<unsigned short>();
			}
		}

		read.close();

		(*def_ptr) = def;
	}

	void ITechset::parse_stateinfo(const std::string& techset, Material* mat, ZoneMemory* mem)
	{
		const auto path = "techsets\\state\\"s + techset + ".stateinfo"s;
		filesystem::file file(path);
		if (file.exists())
		{
			file.open("rb");
			const auto size = file.size();
			auto bytes = file.read_bytes(size);
			file.close();

			auto stateInfo = json::parse(bytes);

			mat->stateFlags = stateInfo["stateFlags"].get<unsigned char>();

			return;
		}
		ZONETOOL_FATAL("stateinfo for techset \"%s\" are missing!", techset.data());
	}

	void ITechset::parse_statebits(const std::string& techset, unsigned char* statebits, ZoneMemory* mem)
	{
		const auto path = "techsets\\state\\" + techset + ".statebits";
		auto file = filesystem::file(path);
		file.open("rb");
		auto fp = file.get_fp();

		if (fp)
		{
			fread(statebits, TECHNIQUES_COUNT, 1, fp);
			file.close();
			return;
		}

		ZONETOOL_FATAL("statebits for techset \"%s\" are missing!", techset.data());
	}

	void ITechset::parse_statebitsmap(const std::string& techset, GfxStateBits** map, unsigned char* count,
		std::vector<std::array<std::uint64_t, 10>>* dssb,
		std::vector<std::array<std::uint32_t, 3>>* bsb,
		ZoneMemory* mem)
	{
		const auto path = "techsets\\state\\"s + techset + ".statebitsmap"s;
		filesystem::file file(path);
		if (file.exists())
		{
			file.open("rb");
			const auto size = file.size();
			auto bytes = file.read_bytes(size);
			file.close();

			auto stateMap = json::parse(bytes);
			if (stateMap.size() > 0)
			{
				auto stateBits = mem->Alloc<GfxStateBits>(stateMap.size());
				for (int i = 0; i < stateMap.size(); i++)
				{
					stateBits[i].loadBits[0] = stateMap[i]["loadBits"][0].get<unsigned int>();
					stateBits[i].loadBits[1] = stateMap[i]["loadBits"][1].get<unsigned int>();
					stateBits[i].loadBits[2] = stateMap[i]["loadBits"][2].get<unsigned int>();
					stateBits[i].loadBits[3] = stateMap[i]["loadBits"][3].get<unsigned int>();
					stateBits[i].loadBits[4] = stateMap[i]["loadBits"][4].get<unsigned int>();
					stateBits[i].loadBits[5] = stateMap[i]["loadBits"][5].get<unsigned int>();

					std::array<std::uint64_t, 10> temp_bits = { 0 };
					for (int j = 0; j < 10; j++)
					{
						temp_bits[j] = stateMap[i]["depthStencilStateBits"][j].get<std::uint64_t>();
					}
					dssb->push_back(std::move(temp_bits));

					std::array<std::uint32_t, 3> temp_bits2;
					for (int j = 0; j < 3; j++)
					{
						temp_bits2[j] = stateMap[i]["blendStateBits"][j].get<std::uint32_t>();
					}
					bsb->push_back(std::move(temp_bits2));

					stateBits[i].rasterizerState = stateMap[i]["rasterizerState"].get<unsigned char>();
				}
				(*map) = stateBits;
			}
			else
			{
				(*map) = nullptr;
			}
			*count = static_cast<unsigned char>(stateMap.size());
			return;
		}
		ZONETOOL_FATAL("statebitsmap for techset \"%s\" are missing!", techset.data());
	}

	void ITechset::init(const std::string& name, ZoneMemory* mem)
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
			this->asset_ = DB_FindXAssetHeader_Safe(XAssetType(this->type()), this->name().data()).techniqueSet;
			if (DB_IsXAssetDefault(XAssetType(this->type()), this->name().data()))
			{
				ZONETOOL_FATAL("techset \"%s\" not found.", name.data());
			}
		}
	}

	void ITechset::prepare(ZoneBuffer* buf, ZoneMemory* mem)
	{
		auto data = this->asset_;
		for (auto technique = 0u; technique < TECHNIQUES_COUNT; technique++)
		{
			if (data->techniques[technique])
			{
				for (unsigned short pass = 0; pass < data->techniques[technique]->hdr.passCount; pass++)
				{
					auto& techniquePass = data->techniques[technique]->passArray[pass];
					if (techniquePass.perPrimArgSize)
					{
						techniquePass.perPrimConstantBuffer = buf->write_ppas(techniquePass.perPrimArgSize);
					}
					if (techniquePass.perObjArgSize)
					{
						techniquePass.perObjConstantBuffer = buf->write_poas(techniquePass.perObjArgSize);
					}
					if (techniquePass.stableArgSize)
					{
						techniquePass.stableConstantBuffer = buf->write_sas(techniquePass.stableArgSize);
					}
				}
			}
		}
	}

	void ITechset::load_depending(IZone* zone)
	{
		auto data = this->asset_;

		for (auto technique = 0u; technique < TECHNIQUES_COUNT; technique++)
		{
			if (data->techniques[technique])
			{
				for (unsigned short pass = 0; pass < data->techniques[technique]->hdr.passCount; pass++)
				{
					auto& techniquePass = data->techniques[technique]->passArray[pass];

					if (techniquePass.vertexShader)
					{
						zone->add_asset_of_type(ASSET_TYPE_VERTEXSHADER, techniquePass.vertexShader->name);
					}

					/*if (techniquePass.vertexDecl)
					{
						zone->add_asset_of_type(ASSET_TYPE_VERTEXDECL, techniquePass.vertexDecl->name);
					}*/

					if (techniquePass.hullShader)
					{
						zone->add_asset_of_type(ASSET_TYPE_HULLSHADER, techniquePass.hullShader->name);
					}

					if (techniquePass.domainShader)
					{
						zone->add_asset_of_type(ASSET_TYPE_DOMAINSHADER, techniquePass.domainShader->name);
					}

					if (techniquePass.pixelShader)
					{
						zone->add_asset_of_type(ASSET_TYPE_PIXELSHADER, techniquePass.pixelShader->name);
					}
				}
			}
		}
	}

	std::string ITechset::name()
	{
		return this->name_;
	}

	std::int32_t ITechset::type()
	{
		return ASSET_TYPE_TECHNIQUE_SET;
	}

	void ITechset::write(IZone* zone, ZoneBuffer* buf)
	{
		auto* data = this->asset_;
		auto* dest = buf->write(data);

		buf->push_stream(3);

		dest->name = buf->write_str(this->name());

		for (auto technique = 0; technique < TECHNIQUES_COUNT; technique++)
		{
			if (!data->techniques[technique])
			{
				continue;
			}

			buf->align(3);

			auto* technique_header = buf->write(&data->techniques[technique]->hdr);
			auto* technique_passes = buf->write(data->techniques[technique]->passArray, technique_header->passCount);

			for (unsigned short pass = 0; pass < technique_header->passCount; pass++)
			{
				if (technique_passes[pass].vertexShader)
				{
					technique_passes[pass].vertexShader =
						reinterpret_cast<MaterialVertexShader*>(zone->get_asset_pointer(
						ASSET_TYPE_VERTEXSHADER, technique_passes[pass].vertexShader->name));
				}

				if (technique_passes[pass].vertexDecl)
				{
					/*technique_passes[pass].vertexDecl =
						reinterpret_cast<MaterialVertexDeclaration*>(zone->get_asset_pointer(
							ASSET_TYPE_VERTEXDECL, technique_passes[pass].vertexDecl->name));*/
					std::uintptr_t ptr = get_vertexdecl_pointer(technique_passes[pass].vertexDecl->name);
					if (ptr)
					{
						technique_passes[pass].vertexDecl = reinterpret_cast<MaterialVertexDeclaration*>(ptr);
					}
					else
					{
						buf->push_stream(0);

						buf->push_stream(3);
						buf->align(7);
						ptr = 0xFDFDFDF300000000 + buf->stream_offset(3) + 1;
						add_vertexdecl_pointer(technique_passes[pass].vertexDecl->name, ptr);
						buf->inc_stream(3, 8);
						buf->pop_stream();

						auto vertexDecl = buf->write(data->techniques[technique]->passArray[pass].vertexDecl);

						buf->push_stream(3);
						if (data->techniques[technique]->passArray[pass].vertexDecl->name)
						{
							vertexDecl->name = buf->write_str(data->techniques[technique]->passArray[pass].vertexDecl->name);
						}
						buf->pop_stream();

						buf->pop_stream();

						ZoneBuffer::insert_pointer(&technique_passes[pass].vertexDecl);
					}
				}

				if (technique_passes[pass].hullShader)
				{
					technique_passes[pass].hullShader =
						reinterpret_cast<MaterialHullShader*>(zone->get_asset_pointer(
						ASSET_TYPE_HULLSHADER, technique_passes[pass].hullShader->name));
				}

				if (technique_passes[pass].domainShader)
				{
					technique_passes[pass].domainShader =
						reinterpret_cast<MaterialDomainShader*>(zone->get_asset_pointer(
						ASSET_TYPE_DOMAINSHADER, technique_passes[pass].domainShader->name));
				}

				if (technique_passes[pass].pixelShader)
				{
					technique_passes[pass].pixelShader =
						reinterpret_cast<MaterialPixelShader*>(zone->get_asset_pointer(
						ASSET_TYPE_PIXELSHADER, technique_passes[pass].pixelShader->name));
				}

				if (technique_passes[pass].args)
				{
					buf->align(3);
					technique_passes[pass].args = buf->write(data->techniques[technique]->passArray[pass].args,
						technique_passes[pass].perPrimArgCount +
						technique_passes[pass].perObjArgCount +
						technique_passes[pass].stableArgCount);

					for (auto arg = 0; arg <
						technique_passes[pass].perPrimArgCount +
						technique_passes[pass].perObjArgCount +
						technique_passes[pass].stableArgCount; arg++)
					{
						if (technique_passes[pass].args[arg].type == 4)
						{
							if (technique_passes[pass].args[arg].u.literalConst)
							{
								technique_passes[pass].args[arg].u.literalConst = buf->write_s(3,
									technique_passes[pass].args[arg].u.literalConst, 4);
							}
						}
					}
				}
			}

			buf->write_str(technique_header->name);
			ZoneBuffer::clear_pointer(&technique_header->name);

			ZoneBuffer::clear_pointer(&dest->techniques[technique]);
		}

		buf->pop_stream();
	}

	void ITechset::dump_constant_buffer_indexes(const std::string& techset, unsigned char* cbi)
	{
		const auto path = "techsets\\constantbuffer\\"s + techset + ".cbi";
		auto file = filesystem::file(path);
		file.open("wb");
		auto fp = file.get_fp();

		if (fp)
		{
			fwrite(cbi, TECHNIQUES_COUNT, 1, fp);
			file.close();
		}
	}

	void ITechset::dump_constant_buffer_def_array(const std::string& techset, unsigned char count, MaterialConstantBufferDef* def)
	{
		const auto path = "techsets\\constantbuffer\\"s + techset + ".cbt";
		assetmanager::dumper dump;
		if (!dump.open(path))
		{
			return;
		}

		dump.dump_int(count);
		dump.dump_array(def, count);
		for (int i = 0; i < count; i++)
		{
			if (def[i].vsData)
			{
				dump.dump_array(def[i].vsData, def[i].vsDataSize);
			}
			if (def[i].hsData)
			{
				dump.dump_array(def[i].hsData, def[i].hsDataSize);
			}
			if (def[i].dsData)
			{
				dump.dump_array(def[i].dsData, def[i].dsDataSize);
			}
			if (def[i].psData)
			{
				dump.dump_array(def[i].psData, def[i].psDataSize);
			}
			if (def[i].vsOffsetData)
			{
				dump.dump_array(def[i].vsOffsetData, def[i].vsOffsetDataSize);
			}
			if (def[i].hsOffsetData)
			{
				dump.dump_array(def[i].hsOffsetData, def[i].hsOffsetDataSize);
			}
			if (def[i].dsOffsetData)
			{
				dump.dump_array(def[i].dsOffsetData, def[i].dsOffsetDataSize);
			}
			if (def[i].psOffsetData)
			{
				dump.dump_array(def[i].psOffsetData, def[i].psOffsetDataSize);
			}
		}

		dump.close();
	}

	void ITechset::dump_stateinfo(const std::string& techset, Material* mat)
	{
		const auto path = "techsets\\state\\"s + techset + ".stateinfo";

		ordered_json json_data = {};

		json_data["stateFlags"] = mat->stateFlags;

		auto file = filesystem::file(path);
		file.open("wb");
		auto fp = file.get_fp();
		if (fp)
		{
			const auto json_dump = json_data.dump(4);
			file.write(json_dump.data(), json_dump.size(), 1);
			file.close();
		}
	}

	void ITechset::dump_statebits(const std::string& techset, unsigned char* statebits)
	{
		const auto path = "techsets\\state\\"s + techset + ".statebits";
		auto file = filesystem::file(path);
		file.open("wb");
		auto fp = file.get_fp();

		if (fp)
		{
			fwrite(statebits, TECHNIQUES_COUNT, 1, fp);
			file.close();
		}
	}

	void ITechset::dump_statebits_map(const std::string& techset, GfxStateBits* map, unsigned char count)
	{
		const auto path = "techsets\\state\\"s + techset + ".statebitsmap";

		ordered_json json_data = {};
		for (unsigned char i = 0; i < count; i++)
		{
			XGfxGlobals* varXGfxGlobals = GetXGfxGlobalsForZone(map[i].zone);
			ordered_json entry;
			entry["loadBits"][0] = map[i].loadBits[0];
			entry["loadBits"][1] = map[i].loadBits[1];
			entry["loadBits"][2] = map[i].loadBits[2];
			entry["loadBits"][3] = map[i].loadBits[3];
			entry["loadBits"][4] = map[i].loadBits[4];
			entry["loadBits"][5] = map[i].loadBits[5];
			for (int j = 0; j < 11; j++)
			{
				entry["depthStencilStateBits"][j] = varXGfxGlobals ? varXGfxGlobals->depthStencilStateBits[map[i].depthStencilState[j]] : 0;
			}
			for (int j = 0; j < 3; j++)
			{
				entry["blendStateBits"][j] = varXGfxGlobals ? varXGfxGlobals->blendStateBits[map[i].blendState][j] : 0;
			}
			entry["rasterizerState"] = map[i].rasterizerState;
			json_data[i] = entry;
		}

		auto file = filesystem::file(path);
		file.open("wb");
		auto fp = file.get_fp();
		if (fp)
		{
			const auto json_dump = json_data.dump(4);
			file.write(json_dump.data(), json_dump.size(), 1);
			file.close();
		}
	}

	void ITechset::dump_technique(MaterialTechnique* asset)
	{
		const auto path = "techsets\\"s + asset->hdr.name + ".technique";

		assetmanager::dumper dumper;
		if (!dumper.open(path))
		{
			return;
		}

		dumper.dump_single(&asset->hdr);
		dumper.dump_array(asset->passArray, asset->hdr.passCount);

		dumper.dump_string(asset->hdr.name);
		for (unsigned short i = 0; i < asset->hdr.passCount; i++)
		{
			if (asset->passArray[i].vertexShader)
			{
				dumper.dump_asset(asset->passArray[i].vertexShader);
				//IVertexShader::dump(asset->passArray[i].vertexShader);
			}

			if (asset->passArray[i].vertexDecl)
			{
				dumper.dump_asset(asset->passArray[i].vertexDecl);
				IVertexDecl::dump(asset->passArray[i].vertexDecl);
			}

			if (asset->passArray[i].hullShader)
			{
				dumper.dump_asset(asset->passArray[i].hullShader);
				//IHullShader::dump(asset->passArray[i].hullShader);
			}

			if (asset->passArray[i].domainShader)
			{
				dumper.dump_asset(asset->passArray[i].domainShader);
				//IDomainShader::dump(asset->passArray[i].domainShader);
			}

			if (asset->passArray[i].pixelShader)
			{
				dumper.dump_asset(asset->passArray[i].pixelShader);
				//IPixelShader::dump(asset->passArray[i].pixelShader);
			}

			if (asset->passArray[i].args)
			{
				dumper.dump_array(asset->passArray[i].args, asset->passArray[i].perObjArgCount + asset->passArray[i].perPrimArgCount + asset->passArray[i].stableArgCount);
				for (auto arg = 0; arg < asset->passArray[i].perObjArgCount + asset->passArray[i].perPrimArgCount + asset->passArray[i].stableArgCount; arg++)
				{
					if (asset->passArray[i].args[arg].type == 4)
					{
						dumper.dump_array(const_cast<float*>(asset->passArray[i].args[arg].u.literalConst), 4);
					}
				}
			}
		}

		dumper.close();
	}

	void yeet(MaterialTechniqueSet* asset)
	{
		const auto path = "techsets\\"s + asset->name + ".techset.txt";

		filesystem::file file(path);
		file.open("wb");
		auto fp = file.get_fp();

		for (auto i = 0u; i < TECHNIQUES_COUNT; i++)
		{
			if (asset->techniques[i])
			{
				fprintf(fp, "%i: %s\n", i, asset->techniques[i]->hdr.name);
			}
			else
			{
				fprintf(fp, "%i: nullptr\n", i);
			}
		}

		file.close();
	}

	void ITechset::dump(MaterialTechniqueSet* asset)
	{
		const auto path = "techsets\\"s + asset->name + ".techset";

		yeet(asset);

		assetmanager::dumper dumper;
		if (!dumper.open(path))
		{
			return;
		}

		dumper.dump_single(asset);
		dumper.dump_string(asset->name);

		for (auto i = 0u; i < TECHNIQUES_COUNT; i++)
		{
			if (asset->techniques[i])
			{
				dumper.dump_string(asset->techniques[i]->hdr.name);
				ITechset::dump_technique(asset->techniques[i]);
			}
		}

		dumper.close();
	}
}