#include <std_include.hpp>
#include "fxworld.hpp"

namespace zonetool
{
	namespace
	{
		h1::FxWorld* convert_to_h1(FxWorld* h2_asset, utils::memory::allocator& allocator)
		{
			const auto asset = allocator.allocate<h1::FxWorld>();
			std::memcpy(asset, h2_asset, sizeof(FxWorld));

			asset->glassSys.piecePlaces = allocator.allocate_array<h1::FxGlassPiecePlace>(asset->glassSys.pieceLimit);
			for (auto i = 0u; i < asset->glassSys.pieceLimit; i++)
			{
				std::memcpy(&asset->glassSys.piecePlaces[i].__s0.frame.quat, &h2_asset->glassSys.piecePlaces[i].__s0.frame.quat,
					sizeof(asset->glassSys.piecePlaces[i].__s0.frame.quat));
				std::memcpy(&asset->glassSys.piecePlaces[i].__s0.frame.origin, &h2_asset->glassSys.piecePlaces[i].__s0.frame.origin,
					sizeof(asset->glassSys.piecePlaces[i].__s0.frame.origin));

				asset->glassSys.piecePlaces[i].__s0.radius = h2_asset->glassSys.piecePlaces[i].__s0.radius;
			}

			asset->glassSys.initPieceStates = allocator.allocate_array<h1::FxGlassInitPieceState>(asset->glassSys.initPieceCount);
			for (auto i = 0u; i < asset->glassSys.initPieceCount; i++)
			{
				std::memcpy(&asset->glassSys.initPieceStates[i].frame.quat, &h2_asset->glassSys.initPieceStates[i].frame.quat,
					sizeof(asset->glassSys.initPieceStates[i].frame.quat));

				std::memcpy(&asset->glassSys.initPieceStates[i].frame.origin, &h2_asset->glassSys.initPieceStates[i].frame.origin,
					sizeof(asset->glassSys.initPieceStates[i].frame.origin));

				asset->glassSys.initPieceStates[i].radius = h2_asset->glassSys.initPieceStates[i].radius;
				asset->glassSys.initPieceStates[i].texCoordOrigin[0] = h2_asset->glassSys.initPieceStates[i].texCoordOrigin[0];
				asset->glassSys.initPieceStates[i].texCoordOrigin[1] = h2_asset->glassSys.initPieceStates[i].texCoordOrigin[1];
				asset->glassSys.initPieceStates[i].supportMask = h2_asset->glassSys.initPieceStates[i].supportMask;
				asset->glassSys.initPieceStates[i].areaX2 = h2_asset->glassSys.initPieceStates[i].areaX2;
				asset->glassSys.initPieceStates[i].lightingIndex = h2_asset->glassSys.initPieceStates[i].lightingIndex;
				asset->glassSys.initPieceStates[i].defIndex = h2_asset->glassSys.initPieceStates[i].defIndex;
				asset->glassSys.initPieceStates[i].vertCount = h2_asset->glassSys.initPieceStates[i].vertCount;
				asset->glassSys.initPieceStates[i].fanDataCount = h2_asset->glassSys.initPieceStates[i].fanDataCount;
				*asset->glassSys.initPieceStates[i].pad = *h2_asset->glassSys.initPieceStates[i].pad;
			}

			return asset;
		}
	}

	FxWorld* IFxWorld::parse(const std::string& name, ZoneMemory* mem)
	{
		return nullptr;
	}

	void IFxWorld::init(const std::string& name, ZoneMemory* mem)
	{
	
	}

	void IFxWorld::prepare(ZoneBuffer* buf, ZoneMemory* mem)
	{
	}

	void IFxWorld::load_depending(IZone* zone)
	{

	}

	std::string IFxWorld::name()
	{
		return this->name_;
	}

	std::int32_t IFxWorld::type()
	{
		return ASSET_TYPE_FX_MAP;
	}

	void IFxWorld::write(IZone* zone, ZoneBuffer* buf)
	{

	}

	void IFxWorld::dump(FxWorld* h2_asset)
	{
		utils::memory::allocator allocator;
		const auto asset = convert_to_h1(h2_asset, allocator);
		const auto path = asset->name + ".fxmap"s;

		assetmanager::dumper write;
		if (!write.open(path))
		{
			return;
		}
		
		write.dump_single(asset);
		write.dump_string(asset->name);

		write.dump_array(asset->glassSys.defs, asset->glassSys.defCount);
		for (unsigned int i = 0; i < asset->glassSys.defCount; i++)
		{
			write.dump_asset(asset->glassSys.defs[i].material);
			write.dump_asset(asset->glassSys.defs[i].materialShattered);

			write.dump_asset(asset->glassSys.defs[i].physPreset);

			write.dump_asset(asset->glassSys.defs[i].pieceBreakEffect);
			write.dump_asset(asset->glassSys.defs[i].shatterEffect);
			write.dump_asset(asset->glassSys.defs[i].shatterSmallEffect);
			write.dump_asset(asset->glassSys.defs[i].crackDecalEffect);

			write.dump_asset(asset->glassSys.defs[i].damagedSound);
			write.dump_asset(asset->glassSys.defs[i].destroyedSound);
			write.dump_asset(asset->glassSys.defs[i].destroyedQuietSound);
		}

		write.dump_array(asset->glassSys.piecePlaces, asset->glassSys.pieceLimit);

		write.dump_array(asset->glassSys.pieceStates, asset->glassSys.pieceLimit);

		write.dump_array(asset->glassSys.pieceDynamics, asset->glassSys.pieceLimit);

		write.dump_array(asset->glassSys.geoData, asset->glassSys.geoDataLimit);

		write.dump_array(asset->glassSys.isInUse, asset->glassSys.pieceWordCount);

		write.dump_array(asset->glassSys.cellBits, asset->glassSys.pieceWordCount * asset->glassSys.cellCount);

		write.dump_array(asset->glassSys.visData, (asset->glassSys.pieceLimit + 15) & 0xFFFFFFF0);

		write.dump_array(asset->glassSys.linkOrg, asset->glassSys.pieceLimit);

		write.dump_array(asset->glassSys.halfThickness, (asset->glassSys.pieceLimit + 3) & 0xFFFFFFFC);

		write.dump_array(asset->glassSys.lightingHandles, asset->glassSys.initPieceCount);

		write.dump_array(asset->glassSys.initGeoData, asset->glassSys.initGeoDataCount);

		write.dump_array(asset->glassSys.initPieceStates, asset->glassSys.initPieceCount);

		write.close();
	}
}