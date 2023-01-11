#include <std_include.hpp>
#include "comworld.hpp"

namespace zonetool
{
	namespace
	{
#define COPY_VALUE(name) \
		lights[i].name = h2_lights[i].name; \

#define COPY_ARR(name) \
		std::memcpy(&lights[i].name, &h2_lights[i].name, sizeof(lights[i].name)); \

		h1::ComPrimaryLight* convert_primary_lights(ComPrimaryLight* h2_lights, const unsigned int count,
			utils::memory::allocator& allocator)
		{
			const auto lights = allocator.allocate_array<h1::ComPrimaryLight>(count);

			for (auto i = 0u; i < count; i++)
			{
				lights[i].type = static_cast<h1::GfxLightType>(h2_lights[i].type);
				COPY_VALUE(canUseShadowMap);
				COPY_VALUE(needsDynamicShadows);
				COPY_VALUE(exponent);
				COPY_VALUE(isVolumetric);
				COPY_ARR(color);
				COPY_ARR(dir);
				COPY_ARR(up);
				COPY_ARR(origin);
				COPY_ARR(fadeOffset);
				COPY_VALUE(bulbRadius);
				COPY_ARR(bulbLength);
				COPY_VALUE(radius);
				COPY_VALUE(cosHalfFovOuter);
				COPY_VALUE(cosHalfFovInner);
				COPY_VALUE(cosHalfFovExpanded);
				COPY_VALUE(rotationLimit);
				COPY_VALUE(translationLimit);
				COPY_VALUE(cucRotationOffsetRad);
				COPY_VALUE(cucRotationSpeedRad);
				COPY_ARR(cucScrollVector);
				COPY_ARR(cucScaleVector);
				COPY_ARR(cucTransVector);
				lights[i].defName = h2_lights[i].defName;
			}
			
			return lights;
		}
	}

	ComWorld* IComWorld::parse(const std::string& name, ZoneMemory* mem)
	{
		return nullptr;
	}

	void IComWorld::init(const std::string& name, ZoneMemory* mem)
	{

	}

	void IComWorld::prepare(ZoneBuffer* buf, ZoneMemory* mem)
	{
	}

	void IComWorld::load_depending(IZone* zone)
	{

	}

	std::string IComWorld::name()
	{
		return this->name_;
	}

	std::int32_t IComWorld::type()
	{
		return ASSET_TYPE_COM_MAP;
	}

	void IComWorld::write(IZone* zone, ZoneBuffer* buf)
	{

	}

	void IComWorld::dump(ComWorld* h2_asset)
	{
		utils::memory::allocator allocator;
		const auto asset = allocator.allocate<h1::ComWorld>();
		std::memcpy(asset, h2_asset, sizeof(h1::ComWorld));

		const auto path = asset->name + ".commap"s;

		assetmanager::dumper write;
		if (!write.open(path))
		{
			return;
		}

		asset->primaryLights = convert_primary_lights(h2_asset->primaryLights,
			asset->primaryLightCount, allocator);

		write.dump_single(asset);
		write.dump_string(asset->name);

		write.dump_array(asset->primaryLights, asset->primaryLightCount);
		for (unsigned int i = 0; i < asset->primaryLightCount; i++)
		{
			write.dump_string(asset->primaryLights[i].defName);
		}
		write.dump_array(asset->primaryLightEnvs, asset->primaryLightEnvCount);

		write.close();
	}
}