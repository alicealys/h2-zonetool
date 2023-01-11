#include <std_include.hpp>
#include "techset.hpp"

#include "vertexshader.hpp"
#include "vertexdecl.hpp"
#include "hullshader.hpp"
#include "domainshader.hpp"
#include "pixelshader.hpp"

namespace zonetool
{
	namespace
	{
		h1::MaterialTechniqueSet* convert_to_h1(MaterialTechniqueSet* h2_asset, utils::memory::allocator& allocator)
		{
			const auto asset = allocator.allocate<h1::MaterialTechniqueSet>();
			asset->name = allocator.duplicate_string(h2_asset->name);
			asset->flags = h2_asset->flags;
			asset->worldVertFormat = h2_asset->worldVertFormat;
			asset->preDisplacementOnlyCount = h2_asset->preDisplacementOnlyCount;

			std::vector<int> debug_tech_indexes = {59, 122, 185, 248};
			auto current_debug_tech = 0;
			auto h2_tecniques_index = 0;
			for (auto i = 0u; i < TECHNIQUES_COUNT; i++)
			{
				const auto tech = reinterpret_cast<h1::MaterialTechnique*>(h2_asset->techniques[h2_tecniques_index]);
				if (tech != nullptr)
				{
					const auto size = sizeof(MaterialTechniqueHeader) + sizeof(MaterialPass) * tech->hdr.passCount;
					asset->techniques[i] = reinterpret_cast<h1::MaterialTechnique*>(
						allocator.allocate(size));
					std::memcpy(asset->techniques[i], tech, size);
					asset->techniques[i]->hdr.name = allocator.duplicate_string(add_postfix(asset->techniques[i]->hdr.name));
				}
				else
				{
					asset->techniques[i] = nullptr;
				}

				if (current_debug_tech < debug_tech_indexes.size()
					&& h2_tecniques_index == debug_tech_indexes[current_debug_tech])
				{
					++current_debug_tech;
					h2_tecniques_index += 3;
				}

				++h2_tecniques_index;
			}

			return asset;
		}

		unsigned char* convert_to_h1(unsigned char* h2_array, utils::memory::allocator& allocator)
		{
			const auto array = allocator.allocate_array<unsigned char>(TECHNIQUES_COUNT);

			std::vector<int> debug_tech_indexes = {59, 119, 179, 239};
			auto current_debug_tech = 0;
			auto h2_tecniques_index = 0;
			for (auto i = 0u; i < TECHNIQUES_COUNT; i++)
			{
				array[i] = h2_array[h2_tecniques_index];
				if (current_debug_tech < debug_tech_indexes.size() && h2_tecniques_index == debug_tech_indexes[current_debug_tech])
				{
					++current_debug_tech;
					h2_tecniques_index += 3;
				}

				++h2_tecniques_index;
			}

			return array;
		}

		unsigned short convert_code_const(unsigned short index)
		{
			if (index < 364)
			{
				if (index <= 342 + 15 && index >= 338 + 15)
				{
					return index - 15;
				}

				if (index >= 312 + 14)
				{
					return index - 14;
				}

				if (index >= 238 + 13)
				{
					return index - 13;
				}

				if (index >= 229 + 4)
				{
					return index - 4;
				}

				if (index >= 212 + 3)
				{
					return index - 3;
				}

				if (index >= 149 + 2) // not sure about this one (between 129-155)
				{
					return index - 2;
				}

				if (index >= 80 + 1)
				{
					return index - 1;
				}

				return index;
			}
			else
			{
				return index - 14;
			}
		}

		MaterialShaderArgument* convert_shader_arguments(MaterialPass* pass, MaterialShaderArgument* args, utils::memory::allocator& allocator)
		{
			const auto arg_count = pass->perPrimArgCount + pass->perObjArgCount + pass->stableArgCount;
			const auto converted_args = allocator.allocate_array<MaterialShaderArgument>(arg_count);
			std::memcpy(converted_args, args, sizeof(MaterialShaderArgument) * arg_count);

			for (auto i = 0; i < arg_count; i++)
			{
				if (converted_args[i].type != 0)
				{
					continue;
				}

				converted_args[i].u.codeConst.index = convert_code_const(converted_args[i].u.codeConst.index);
			}

			return converted_args;
		}
	}

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
		return nullptr;
	}

	MaterialTechniqueSet* ITechset::parse(const std::string& name, ZoneMemory* mem)
	{
		return nullptr;
	}

	void ITechset::parse_constant_buffer_indexes(const std::string& techset, unsigned char* indexes, ZoneMemory* mem)
	{

	}

	void ITechset::parse_constant_buffer_def_array(const std::string& techset, MaterialConstantBufferDef** def_ptr, unsigned char* count, ZoneMemory* mem)
	{

	}

	void ITechset::parse_stateinfo(const std::string& techset, Material* mat, ZoneMemory* mem)
	{

	}

	void ITechset::parse_statebits(const std::string& techset, unsigned char* statebits, ZoneMemory* mem)
	{

	}

	void ITechset::parse_statebitsmap(const std::string& techset, GfxStateBits** map, unsigned char* count,
		std::vector<std::array<std::uint64_t, 10>>* dssb,
		std::vector<std::array<std::uint32_t, 3>>* bsb,
		ZoneMemory* mem)
	{

	}

	void ITechset::init(const std::string& name, ZoneMemory* mem)
	{

	}

	void ITechset::prepare(ZoneBuffer* buf, ZoneMemory* mem)
	{

	}

	void ITechset::load_depending(IZone* zone)
	{

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

	}

	void ITechset::dump_constant_buffer_indexes(const std::string& techset, unsigned char* h2_cbi)
	{
		utils::memory::allocator allocator;
		const auto path = "techsets\\constantbuffer\\"s + techset + ".cbi";
		auto file = filesystem::file(path);
		file.open("wb");
		auto fp = file.get_fp();
		const auto cbi = convert_to_h1(h2_cbi, allocator);

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

	void ITechset::dump_statebits(const std::string& techset, unsigned char* h2_statebits)
	{
		utils::memory::allocator allocator;
		const auto path = "techsets\\state\\"s + techset + ".statebits";
		auto file = filesystem::file(path);
		file.open("wb");
		auto fp = file.get_fp();
		const auto statebits = convert_to_h1(h2_statebits, allocator);

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

		utils::memory::allocator allocator;

		dumper.dump_single(&asset->hdr);
		const auto pass_array = allocator.allocate_array<MaterialPass>(asset->hdr.passCount);
		std::memcpy(pass_array, asset->passArray, sizeof(MaterialPass) * asset->hdr.passCount);
		for (auto i = 0; i < asset->hdr.passCount; i++)
		{
			pass_array[i].stableArgSize -= 16;
		}
		dumper.dump_array(pass_array, asset->hdr.passCount);

		dumper.dump_string(asset->hdr.name);
		for (unsigned short i = 0; i < asset->hdr.passCount; i++)
		{
			if (asset->passArray[i].vertexShader)
			{
				const auto vertex_shader = allocator.allocate<MaterialVertexShader>();
				std::memcpy(vertex_shader, asset->passArray[i].vertexShader, sizeof(MaterialVertexShader));
				vertex_shader->name = allocator.duplicate_string(add_postfix(vertex_shader->name));
				dumper.dump_asset(vertex_shader);
				//IVertexShader::dump(asset->passArray[i].vertexShader);
			}

			if (asset->passArray[i].vertexDecl)
			{
				const auto vertex_decl = allocator.allocate<MaterialVertexDeclaration>();
				std::memcpy(vertex_decl, asset->passArray[i].vertexDecl, sizeof(MaterialVertexDeclaration));
				vertex_decl->name = allocator.duplicate_string(add_postfix(vertex_decl->name));
				dumper.dump_asset(vertex_decl);
				IVertexDecl::dump(reinterpret_cast<MaterialVertexDeclaration*>(asset->passArray[i].vertexDecl));
			}

			if (asset->passArray[i].hullShader)
			{
				const auto hull_shader = allocator.allocate<MaterialHullShader>();
				std::memcpy(hull_shader, asset->passArray[i].hullShader, sizeof(MaterialHullShader));
				hull_shader->name = allocator.duplicate_string(add_postfix(hull_shader->name));
				dumper.dump_asset(hull_shader);
				//IHullShader::dump(asset->passArray[i].hullShader);
			}

			if (asset->passArray[i].domainShader)
			{
				const auto domain_shader = allocator.allocate<MaterialDomainShader>();
				std::memcpy(domain_shader, asset->passArray[i].domainShader, sizeof(MaterialDomainShader));
				domain_shader->name = allocator.duplicate_string(add_postfix(domain_shader->name));
				dumper.dump_asset(domain_shader);
				//IDomainShader::dump(asset->passArray[i].domainShader);
			}

			if (asset->passArray[i].pixelShader)
			{
				const auto pixel_shader = allocator.allocate<MaterialPixelShader>();
				std::memcpy(pixel_shader, asset->passArray[i].pixelShader, sizeof(MaterialPixelShader));
				pixel_shader->name = allocator.duplicate_string(add_postfix(pixel_shader->name));
				dumper.dump_asset(pixel_shader);
				//IPixelShader::dump(asset->passArray[i].pixelShader);
			}

			if (asset->passArray[i].args)
			{
				const auto arg_count = asset->passArray[i].perObjArgCount + asset->passArray[i].perPrimArgCount + asset->passArray[i].stableArgCount;
				const auto converted_args = convert_shader_arguments(&asset->passArray[i], asset->passArray[i].args, allocator);
				dumper.dump_array(converted_args, arg_count);

				for (auto arg = 0; arg < arg_count; arg++)
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

	void yeet(h1::MaterialTechniqueSet* asset)
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

	void ITechset::dump(MaterialTechniqueSet* h2_asset)
	{
		utils::memory::allocator allocator;
		const auto asset = convert_to_h1(h2_asset, allocator);
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
				ITechset::dump_technique(reinterpret_cast<MaterialTechnique*>(asset->techniques[i]));
			}
		}

		dumper.close();
	}
}