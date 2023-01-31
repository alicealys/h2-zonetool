#include <std_include.hpp>
#include "gfxworld.hpp"

namespace zonetool
{
	namespace
	{
#define COPY_VALUE(name) \
		static_assert(sizeof(asset->name) == sizeof(h2_asset->name)); \
		asset->name = h2_asset->name;

#define COPY_VALUE_CAST(name) \
		static_assert(sizeof(asset->name) == sizeof(h2_asset->name)); \
		asset->name = *reinterpret_cast<decltype(asset->name)*>(&h2_asset->name);

#define COPY_ARR(name) \
		static_assert(sizeof(asset->name) == sizeof(h2_asset->name)); \
		std::memcpy(&asset->name, &h2_asset->name, sizeof(asset->name));

#define REINTERPRET_CAST_SAFE(name) \
		static_assert(sizeof(*asset->name) == sizeof(*h2_asset->name)); \
		asset->name = reinterpret_cast<decltype(asset->name)>(h2_asset->name);

#define REINTERPRET_CAST_SAFE_ARR(name, count) \
		for (auto i_ = 0; i_ < count; i_++) \
		{ \
			REINTERPRET_CAST_SAFE(name[i_]); \
		} \

		h1::GfxWorld* convert_to_h1(GfxWorld* h2_asset, utils::memory::allocator& allocator)
		{
			const auto asset = allocator.allocate<h1::GfxWorld>();

			REINTERPRET_CAST_SAFE(name);
			REINTERPRET_CAST_SAFE(baseName);
			COPY_VALUE(bspVersion);
			COPY_VALUE(planeCount);
			//COPY_VALUE(nodeCount);
			COPY_VALUE(surfaceCount);
			COPY_VALUE(skyCount);
			REINTERPRET_CAST_SAFE(skies);
			COPY_VALUE(portalGroupCount);
			COPY_VALUE(lastSunPrimaryLightIndex);
			COPY_VALUE(primaryLightCount);
			COPY_VALUE(primaryLightEnvCount);
			asset->sortKeyLitDecal = 7;
			asset->sortKeyEffectDecal = 43;
			asset->sortKeyTopDecal = 17;
			asset->sortKeyEffectAuto = 53;
			asset->sortKeyDistortion = 48;
			asset->sortKeyUnknown = 18;
			asset->sortKeyUnknown2 = 33;

			{
				COPY_VALUE(dpvsPlanes.cellCount);
				REINTERPRET_CAST_SAFE(dpvsPlanes.planes);
				asset->nodeCount = 2 * h2_asset->nodeCount;
				asset->dpvsPlanes.nodes = allocator.allocate_array<unsigned short>(asset->nodeCount);
				auto node_index = 0;
				for (auto i = 0; i < h2_asset->nodeCount; i++)
				{
					asset->dpvsPlanes.nodes[node_index++] = h2_asset->dpvsPlanes.nodes[i].unk0;
					asset->dpvsPlanes.nodes[node_index++] = h2_asset->dpvsPlanes.nodes[i].unk1 * 2;
				}

				REINTERPRET_CAST_SAFE(dpvsPlanes.sceneEntCellBits);
			}

			REINTERPRET_CAST_SAFE(skies);
			REINTERPRET_CAST_SAFE(aabbTreeCounts);
			REINTERPRET_CAST_SAFE(aabbTrees);
			REINTERPRET_CAST_SAFE(cells);

			asset->portalGroup = allocator.allocate_array<h1::GfxPortalGroup>(asset->portalGroupCount);
			for (auto i = 0u; i < asset->portalGroupCount; i++)
			{
				COPY_VALUE(portalGroup[i].group);
				REINTERPRET_CAST_SAFE(portalGroup[i].info);
				COPY_VALUE(portalGroup[i].infoCount);
			}

			COPY_VALUE(unk_vec4_count_0);
			REINTERPRET_CAST_SAFE(unk_vec4_0);
			COPY_VALUE_CAST(draw);
			COPY_VALUE_CAST(lightGrid);
			COPY_VALUE(modelCount);
			REINTERPRET_CAST_SAFE(models);
			COPY_ARR(mins1);
			COPY_ARR(maxs1);
			COPY_ARR(mins2);
			COPY_ARR(maxs2);
			COPY_VALUE(checksum);
			COPY_VALUE(materialMemoryCount);
			REINTERPRET_CAST_SAFE(materialMemory);
			COPY_VALUE_CAST(sun);
			COPY_ARR(outdoorLookupMatrix);
			REINTERPRET_CAST_SAFE(outdoorImage);
			REINTERPRET_CAST_SAFE(cellCasterBits);
			REINTERPRET_CAST_SAFE(cellHasSunLitSurfsBits);
			REINTERPRET_CAST_SAFE(sceneDynModel);
			REINTERPRET_CAST_SAFE(sceneDynBrush);
			REINTERPRET_CAST_SAFE(primaryLightEntityShadowVis);
			REINTERPRET_CAST_SAFE_ARR(primaryLightDynEntShadowVis, 2);
			REINTERPRET_CAST_SAFE(nonSunPrimaryLightForModelDynEnt);
			REINTERPRET_CAST_SAFE(shadowGeom);
			REINTERPRET_CAST_SAFE(shadowGeomOptimized);
			REINTERPRET_CAST_SAFE(lightRegion);

			// dpvs
			{
				COPY_VALUE(dpvs.smodelCount);
				COPY_VALUE(dpvs.subdivVertexLightingInfoCount);
				COPY_VALUE(dpvs.staticSurfaceCount);
				COPY_VALUE(dpvs.litOpaqueSurfsBegin);
				COPY_VALUE(dpvs.litOpaqueSurfsEnd);
				COPY_VALUE(dpvs.unkSurfsBegin);
				COPY_VALUE(dpvs.unkSurfsEnd);
				COPY_VALUE(dpvs.litDecalSurfsBegin);
				COPY_VALUE(dpvs.litDecalSurfsEnd);
				COPY_VALUE(dpvs.litTransSurfsBegin);
				COPY_VALUE(dpvs.litTransSurfsEnd);
				COPY_VALUE(dpvs.shadowCasterSurfsBegin);
				COPY_VALUE(dpvs.shadowCasterSurfsEnd);
				COPY_VALUE(dpvs.emissiveSurfsBegin);
				COPY_VALUE(dpvs.emissiveSurfsEnd);
				COPY_VALUE(dpvs.smodelVisDataCount);
				COPY_VALUE(dpvs.surfaceVisDataCount);
				REINTERPRET_CAST_SAFE_ARR(dpvs.smodelVisData, 4);
				REINTERPRET_CAST_SAFE_ARR(dpvs.smodelUnknownVisData, 27);
				REINTERPRET_CAST_SAFE_ARR(dpvs.surfaceVisData, 4);
				REINTERPRET_CAST_SAFE_ARR(dpvs.surfaceUnknownVisData, 27);
				REINTERPRET_CAST_SAFE_ARR(dpvs.smodelUmbraVisData, 4);
				REINTERPRET_CAST_SAFE_ARR(dpvs.surfaceUmbraVisData, 4);
				REINTERPRET_CAST_SAFE(dpvs.lodData);
				REINTERPRET_CAST_SAFE(dpvs.tessellationCutoffVisData);
				REINTERPRET_CAST_SAFE(dpvs.sortedSurfIndex);
				REINTERPRET_CAST_SAFE(dpvs.smodelInsts);
				REINTERPRET_CAST_SAFE(dpvs.surfaces);
				REINTERPRET_CAST_SAFE(dpvs.surfacesBounds);

				asset->dpvs.smodelDrawInsts = allocator.allocate_array<h1::GfxStaticModelDrawInst>(asset->dpvs.smodelCount);
				for (auto i = 0u; i < asset->dpvs.smodelCount; i++)
				{
					asset->dpvs.smodelDrawInsts[i].model = allocator.allocate<h1::XModel>();
					asset->dpvs.smodelDrawInsts[i].model->name = h2_asset->dpvs.smodelDrawInsts[i].model->name;
					COPY_VALUE_CAST(dpvs.smodelDrawInsts[i].placement);
					COPY_VALUE(dpvs.smodelDrawInsts[i].cullDist);
					COPY_VALUE(dpvs.smodelDrawInsts[i].flags);
					COPY_VALUE(dpvs.smodelDrawInsts[i].lightingHandle);
					COPY_VALUE(dpvs.smodelDrawInsts[i].staticModelId);
					COPY_VALUE(dpvs.smodelDrawInsts[i].primaryLightEnvIndex);
					COPY_VALUE(dpvs.smodelDrawInsts[i].reflectionProbeIndex);
					COPY_VALUE(dpvs.smodelDrawInsts[i].firstMtlSkinIndex);
					COPY_VALUE(dpvs.smodelDrawInsts[i].sunShadowFlags);
					asset->dpvs.smodelDrawInsts[i].unk0 = 1;
					asset->dpvs.smodelDrawInsts[i].unk1 = h2_asset->dpvs.smodelDrawInsts[i].unk;
				}

				REINTERPRET_CAST_SAFE(dpvs.unknownSModelVisData1);
				REINTERPRET_CAST_SAFE(dpvs.unknownSModelVisData2);
				REINTERPRET_CAST_SAFE(dpvs.smodelLighting);
				REINTERPRET_CAST_SAFE(dpvs.subdivVertexLighting);
				REINTERPRET_CAST_SAFE(dpvs.surfaceMaterials);
				REINTERPRET_CAST_SAFE(dpvs.surfaceCastsSunShadow);
				COPY_VALUE(dpvs.sunShadowOptCount);
				COPY_VALUE(dpvs.sunSurfVisDataCount);
				REINTERPRET_CAST_SAFE(dpvs.surfaceCastsSunShadowOpt);
				REINTERPRET_CAST_SAFE(dpvs.surfaceDeptAndSurf);
				REINTERPRET_CAST_SAFE(dpvs.constantBuffersLit);
				REINTERPRET_CAST_SAFE(dpvs.constantBuffersAmbient);
				COPY_VALUE(dpvs.usageCount);
			}

			COPY_VALUE_CAST(dpvsDyn);
			COPY_VALUE(mapVtxChecksum);
			COPY_VALUE(heroOnlyLightCount);
			REINTERPRET_CAST_SAFE(heroOnlyLights);
			COPY_VALUE(fogTypesAllowed);
			COPY_VALUE(umbraTomeSize);
			REINTERPRET_CAST_SAFE(umbraTomeData);
			COPY_VALUE_CAST(umbraTomePtr);
			COPY_VALUE(mdaoVolumesCount);
			REINTERPRET_CAST_SAFE(mdaoVolumes);
			COPY_VALUE_CAST(buildInfo);

			return asset;
		}
	}

	GfxWorld* IGfxWorld::parse(const std::string& name, ZoneMemory* mem)
	{
		return nullptr;
	}

	void IGfxWorld::init(const std::string& name, ZoneMemory* mem)
	{

	}

	void IGfxWorld::prepare(ZoneBuffer* buf, ZoneMemory* mem)
	{
	}

	void IGfxWorld::load_depending(IZone* zone)
	{

	}

	std::string IGfxWorld::name()
	{
		return this->name_;
	}

	std::int32_t IGfxWorld::type()
	{
		return ASSET_TYPE_GFX_MAP;
	}

	void IGfxWorld::write(IZone* zone, ZoneBuffer* buf)
	{

	}

	void IGfxWorld::dump(GfxWorld* h2_asset)
	{
		utils::memory::allocator allocator;
		const auto asset = convert_to_h1(h2_asset, allocator);
		const auto path = asset->name + ".gfxmap"s;

		assetmanager::dumper write;
		if (!write.open(path))
		{
			return;
		}

		write.dump_single(asset);
		write.dump_string(asset->name);
		write.dump_string(asset->baseName);

		write.dump_array(asset->skies, asset->skyCount);
		for (int i = 0; i < asset->skyCount; i++)
		{
			write.dump_array(asset->skies[i].skyStartSurfs, asset->skies[i].skySurfCount);
			write.dump_asset(asset->skies[i].skyImage);
		}

		write.dump_array(asset->dpvsPlanes.planes, asset->planeCount);
		write.dump_array(asset->dpvsPlanes.nodes, asset->nodeCount);
		write.dump_array(asset->dpvsPlanes.sceneEntCellBits, asset->dpvsPlanes.cellCount << 9);

		write.dump_array(asset->aabbTreeCounts, asset->dpvsPlanes.cellCount);
		write.dump_array(asset->aabbTrees, asset->dpvsPlanes.cellCount);
		for (int i = 0; i < asset->dpvsPlanes.cellCount; i++)
		{
			write.dump_array(asset->aabbTrees[i].aabbTree, asset->aabbTreeCounts[i].aabbTreeCount);
			for (int j = 0; j < asset->aabbTreeCounts[i].aabbTreeCount; j++)
			{
				write.dump_array(asset->aabbTrees[i].aabbTree[j].smodelIndexes,
					asset->aabbTrees[i].aabbTree[j].smodelIndexCount);
			}
		}

		write.dump_array(asset->cells, asset->dpvsPlanes.cellCount);
		for (int i = 0; i < asset->dpvsPlanes.cellCount; i++)
		{
			write.dump_array(asset->cells[i].portals, asset->cells[i].portalCount);
			for (int j = 0; j < asset->cells[i].portalCount; j++)
			{
				write.dump_array(asset->cells[i].portals[j].vertices, asset->cells[i].portals[j].vertexCount);
			}
			write.dump_array(asset->cells[i].reflectionProbes, asset->cells[i].reflectionProbeCount);
			write.dump_array(asset->cells[i].reflectionProbeReferences, asset->cells[i].reflectionProbeReferenceCount);
		}

		write.dump_array(asset->portalGroup, asset->portalGroupCount);
		for (unsigned int i = 0; i < asset->portalGroupCount; i++)
		{
			if (asset->portalGroup[i].group)
			{
				write.dump_string(asset->portalGroup[i].group);
			}

			write.dump_array(asset->portalGroup[i].info, asset->portalGroup[i].infoCount);
		}

		write.dump_array(asset->unk_vec4_0, asset->unk_vec4_count_0);

		write.dump_array(asset->draw.reflectionProbes, asset->draw.reflectionProbeCount);
		for (unsigned int i = 0; i < asset->draw.reflectionProbeCount; i++)
		{
			write.dump_asset(asset->draw.reflectionProbes[i]);
		}

		write.dump_array(asset->draw.reflectionProbeOrigins, asset->draw.reflectionProbeCount);
		for (unsigned int i = 0; i < asset->draw.reflectionProbeCount; i++)
		{
			write.dump_array(asset->draw.reflectionProbeOrigins[i].probeVolumes, asset->draw.reflectionProbeOrigins[i].probeVolumeCount);
			for (unsigned int j = 0; j < asset->draw.reflectionProbeOrigins[i].probeVolumeCount; j++)
			{
				write.dump_array(asset->draw.reflectionProbeOrigins[i].probeVolumes[j].data, asset->draw.reflectionProbeOrigins[i].probeVolumes[j].count);
			}
		}

		write.dump_array(asset->draw.reflectionProbeTextures, asset->draw.reflectionProbeCount);

		write.dump_array(asset->draw.reflectionProbeReferenceOrigins, asset->draw.reflectionProbeReferenceCount);
		write.dump_array(asset->draw.reflectionProbeReferences, asset->draw.reflectionProbeReferenceCount);

		write.dump_array(asset->draw.lightmaps, asset->draw.lightmapCount);
		for (int i = 0; i < asset->draw.lightmapCount; i++)
		{
			write.dump_asset(asset->draw.lightmaps[i].primary);
			write.dump_asset(asset->draw.lightmaps[i].secondary);
		}
		write.dump_array(asset->draw.lightmapPrimaryTextures, asset->draw.lightmapCount);
		write.dump_array(asset->draw.lightmapSecondaryTextures, asset->draw.lightmapCount);
		write.dump_asset(asset->draw.lightmapOverridePrimary);
		write.dump_asset(asset->draw.lightmapOverrideSecondary);

		write.dump_array(asset->draw.vd.vertices, asset->draw.vertexCount);
		write.dump_array(asset->draw.vld.data, asset->draw.vertexLayerDataSize);
		write.dump_array(asset->draw.indices, asset->draw.indexCount);
		write.dump_array(asset->draw.displacementParms, asset->draw.displacementParmsCount);

		write.dump_array(asset->lightGrid.rowDataStart,
			(asset->lightGrid.maxs[asset->lightGrid.rowAxis] - asset->lightGrid.mins[asset->lightGrid.rowAxis] + 1));
		write.dump_array(asset->lightGrid.rawRowData, asset->lightGrid.rawRowDataSize);
		write.dump_array(asset->lightGrid.entries, asset->lightGrid.entryCount);
		write.dump_array(asset->lightGrid.colors, asset->lightGrid.colorCount);

		write.dump_array(asset->lightGrid.stageLightingContrastGain, asset->lightGrid.stageCount);
		write.dump_array(asset->lightGrid.paletteEntryAddress, asset->lightGrid.paletteEntryCount);
		write.dump_array(asset->lightGrid.paletteBitstream, asset->lightGrid.paletteBitstreamSize);

		for (auto i = 0; i < 3; i++)
		{
			write.dump_array(asset->lightGrid.tree[i].p_nodeTable, asset->lightGrid.tree[i].nodeCount);
			write.dump_array(asset->lightGrid.tree[i].p_leafTable, asset->lightGrid.tree[i].leafTableSize);
		}

		write.dump_array(asset->models, asset->modelCount);

		write.dump_array(asset->materialMemory, asset->materialMemoryCount);
		for (int i = 0; i < asset->materialMemoryCount; i++)
		{
			write.dump_asset(asset->materialMemory[i].material);
		}

		write.dump_asset(asset->sun.spriteMaterial);
		write.dump_asset(asset->sun.flareMaterial);

		write.dump_asset(asset->outdoorImage);

		write.dump_array(asset->cellCasterBits,
			asset->dpvsPlanes.cellCount * ((asset->dpvsPlanes.cellCount + 31) >> 5));
		write.dump_array(asset->cellHasSunLitSurfsBits, (asset->dpvsPlanes.cellCount + 31) >> 5);

		write.dump_array(asset->sceneDynModel, asset->dpvsDyn.dynEntClientCount[0]);
		write.dump_array(asset->sceneDynBrush, asset->dpvsDyn.dynEntClientCount[1]);

		write.dump_array(asset->primaryLightEntityShadowVis,
			((asset->primaryLightCount - asset->lastSunPrimaryLightIndex) << 13) - 0x2000);

		write.dump_array(asset->primaryLightDynEntShadowVis[0],
			asset->dpvsDyn.dynEntClientCount[0] * (asset->primaryLightCount - asset->lastSunPrimaryLightIndex - 1));
		write.dump_array(asset->primaryLightDynEntShadowVis[1],
			asset->dpvsDyn.dynEntClientCount[1] * (asset->primaryLightCount - asset->lastSunPrimaryLightIndex - 1));

		write.dump_array(asset->nonSunPrimaryLightForModelDynEnt, asset->dpvsDyn.dynEntClientCount[0]);

		write.dump_array(asset->shadowGeom, asset->primaryLightCount);
		if (asset->shadowGeom)
		{
			for (unsigned int i = 0; i < asset->primaryLightCount; i++)
			{
				write.dump_array(asset->shadowGeom[i].sortedSurfIndex, asset->shadowGeom[i].surfaceCount);
				write.dump_array(asset->shadowGeom[i].smodelIndex, asset->shadowGeom[i].smodelCount);
			}
		}
		write.dump_array(asset->shadowGeomOptimized, asset->primaryLightCount);
		if (asset->shadowGeomOptimized)
		{
			for (unsigned int i = 0; i < asset->primaryLightCount; i++)
			{
				write.dump_array(asset->shadowGeomOptimized[i].sortedSurfIndex, asset->shadowGeomOptimized[i].surfaceCount);
				write.dump_array(asset->shadowGeomOptimized[i].smodelIndex, asset->shadowGeomOptimized[i].smodelCount);
			}
		}

		write.dump_array(asset->lightRegion, asset->primaryLightCount);
		for (unsigned int i = 0; i < asset->primaryLightCount; i++)
		{
			write.dump_array(asset->lightRegion[i].hulls, asset->lightRegion[i].hullCount);
			for (unsigned int j = 0; j < asset->lightRegion[i].hullCount; j++)
			{
				write.dump_array(asset->lightRegion[i].hulls[j].axis, asset->lightRegion[i].hulls[j].axisCount);
			}
		}

		for (auto i = 0; i < 4; i++)
		{
			write.dump_array(asset->dpvs.smodelVisData[i], asset->dpvs.smodelVisDataCount);
		}

		for (auto i = 0; i < 27; i++)
		{
			write.dump_array(asset->dpvs.smodelUnknownVisData[i], asset->dpvs.smodelVisDataCount);
		}

		for (auto i = 0; i < 4; i++)
		{
			write.dump_array(asset->dpvs.surfaceVisData[i], asset->dpvs.surfaceVisDataCount);
		}

		for (auto i = 0; i < 27; i++)
		{
			write.dump_array(asset->dpvs.surfaceUnknownVisData[i], asset->dpvs.surfaceVisDataCount);
		}

		for (auto i = 0; i < 4; i++)
		{
			write.dump_array(asset->dpvs.smodelUmbraVisData[i], asset->dpvs.smodelVisDataCount);
		}

		for (auto i = 0; i < 4; i++)
		{
			write.dump_array(asset->dpvs.surfaceUmbraVisData[i], asset->dpvs.surfaceVisDataCount);
		}

		write.dump_array(asset->dpvs.unknownSModelVisData1, asset->dpvs.smodelVisDataCount);
		write.dump_array(asset->dpvs.unknownSModelVisData2, 2 * asset->dpvs.smodelVisDataCount);

		write.dump_array(asset->dpvs.lodData, asset->dpvs.smodelCount + 1);
		write.dump_array(asset->dpvs.tessellationCutoffVisData, asset->dpvs.surfaceVisDataCount);
		write.dump_array(asset->dpvs.sortedSurfIndex, asset->dpvs.staticSurfaceCount);

		write.dump_array(asset->dpvs.smodelInsts, asset->dpvs.smodelCount);
		write.dump_array(asset->dpvs.surfaces, asset->surfaceCount);
		for (unsigned int i = 0; i < asset->surfaceCount; i++)
		{
			write.dump_asset(asset->dpvs.surfaces[i].material);
		}
		write.dump_array(asset->dpvs.surfacesBounds, asset->surfaceCount);
		write.dump_array(asset->dpvs.smodelDrawInsts, asset->dpvs.smodelCount);
		for (unsigned int i = 0; i < asset->dpvs.smodelCount; i++)
		{
			write.dump_asset(asset->dpvs.smodelDrawInsts[i].model);
		}
		write.dump_array(asset->dpvs.smodelLighting, asset->dpvs.smodelCount);
		for (unsigned int i = 0; i < asset->dpvs.smodelCount; i++)
		{
			auto flags = asset->dpvs.smodelDrawInsts[i].flags;
			if ((flags & 0x180) != 0 && (flags & 0x80) != 0 && asset->dpvs.smodelLighting[i].vertexLightingInfo.lightingValues)
			{
				write.dump_array(asset->dpvs.smodelLighting[i].vertexLightingInfo.lightingValues, asset->dpvs.smodelLighting[i].vertexLightingInfo.numLightingValues);
			}
		}

		write.dump_array(asset->dpvs.subdivVertexLighting, asset->dpvs.subdivVertexLightingInfoCount);

		write.dump_array(asset->dpvs.surfaceMaterials, asset->surfaceCount);
		write.dump_array(asset->dpvs.surfaceCastsSunShadow, asset->dpvs.surfaceVisDataCount);
		write.dump_array(asset->dpvs.surfaceCastsSunShadowOpt, asset->dpvs.sunShadowOptCount * asset->dpvs.sunSurfVisDataCount);

		write.dump_array(asset->dpvs.surfaceDeptAndSurf, asset->dpvs.staticSurfaceCount);

		write.dump_array(asset->dpvs.constantBuffersLit, asset->dpvs.smodelCount);
		for (unsigned int i = 0; i < asset->dpvs.smodelCount; i++)
		{
			write.dump_raw(asset->dpvs.constantBuffersLit[i], 1);
		}
		write.dump_array(asset->dpvs.constantBuffersAmbient, asset->dpvs.smodelCount);
		for (unsigned int i = 0; i < asset->dpvs.smodelCount; i++)
		{
			write.dump_raw(asset->dpvs.constantBuffersAmbient[i], 1);
		}

		write.dump_array(asset->dpvsDyn.dynEntCellBits[0],
			asset->dpvsDyn.dynEntClientWordCount[0] * asset->dpvsPlanes.cellCount);
		write.dump_array(asset->dpvsDyn.dynEntCellBits[1],
			asset->dpvsDyn.dynEntClientWordCount[1] * asset->dpvsPlanes.cellCount);

		write.dump_array(asset->dpvsDyn.dynEntVisData[0][0], asset->dpvsDyn.dynEntClientWordCount[0] * 32);
		write.dump_array(asset->dpvsDyn.dynEntVisData[0][1], asset->dpvsDyn.dynEntClientWordCount[0] * 32);
		write.dump_array(asset->dpvsDyn.dynEntVisData[0][2], asset->dpvsDyn.dynEntClientWordCount[0] * 32);

		write.dump_array(asset->dpvsDyn.dynEntVisData[1][0], asset->dpvsDyn.dynEntClientWordCount[1] * 32);
		write.dump_array(asset->dpvsDyn.dynEntVisData[1][1], asset->dpvsDyn.dynEntClientWordCount[1] * 32);
		write.dump_array(asset->dpvsDyn.dynEntVisData[1][2], asset->dpvsDyn.dynEntClientWordCount[1] * 32);

		write.dump_array(asset->dpvsDyn.dynEntVisData[0][3], asset->dpvsDyn.dynEntClientWordCount[0] * 32);
		write.dump_array(asset->dpvsDyn.dynEntVisData[1][3], asset->dpvsDyn.dynEntClientWordCount[1] * 32);

		write.dump_array(asset->heroOnlyLights, asset->heroOnlyLightCount);

		write.dump_array(asset->umbraTomeData, asset->umbraTomeSize);

		write.dump_array(asset->mdaoVolumes, asset->mdaoVolumesCount);
		for (unsigned int i = 0; i < asset->mdaoVolumesCount; i++)
		{
			write.dump_asset(asset->mdaoVolumes[i].volumeData);
		}

		write.dump_string(asset->buildInfo.args0);
		write.dump_string(asset->buildInfo.args1);
		write.dump_string(asset->buildInfo.buildStartTime);
		write.dump_string(asset->buildInfo.buildEndTime);

		write.close();
	}
}