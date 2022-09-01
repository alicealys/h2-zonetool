#pragma once

namespace zonetool
{
	extern const char* get_asset_name(XAssetType type, void* pointer);
	extern const char* get_asset_name(XAsset* asset);
	extern const char* type_to_string(XAssetType type);
	extern std::int32_t type_to_int(std::string type);

	extern bool zone_exists(const std::string& zone);

	extern XGfxGlobals* GetXGfxGlobalsForCurrentZone();
	extern XGfxGlobals* GetXGfxGlobalsForZone(std::uint32_t zone_index);

	extern XAssetHeader DB_FindXAssetHeader_Safe(XAssetType type, const std::string& name);
	extern void DB_EnumXAssets(const XAssetType type, const std::function<void(XAssetHeader)>& callback, const bool includeOverride);

	WEAK game::symbol<void(XAssetType type, void(__cdecl* func)(XAssetHeader, void*), 
		const void* inData, bool includeOverride)> DB_EnumXAssets_Internal{0x1404129F0};
	WEAK game::symbol<const char* (const XAsset* asset)> DB_GetXAssetName{0x1403E4090};
	WEAK game::symbol<void(const XAsset* asset, const char* name) > DB_SetXAssetName{0x1403E44E0};
	WEAK game::symbol<XAssetHeader(XAssetType type, const char* name, int createDefault)> DB_FindXAssetHeader{0x140412F60};
	WEAK game::symbol<XAssetEntry* (XAssetType type, const char* name)> DB_FindXAssetEntry{0x140412E90};
	WEAK game::symbol<bool(XAssetType, const char* name)> DB_IsXAssetDefault{0x1404143C0};
	WEAK game::symbol<void(XZoneInfo* zoneInfo, unsigned int zoneCount, DBSyncMode syncMode)> DB_LoadXAssets{0x140414FF0};
	WEAK game::symbol<bool(const char* zone, int source)> DB_FileExists{0x140412B50};
	WEAK game::symbol<size_t(XAssetType type)> DB_GetXAssetTypeSize{0x1403E40D0};

	WEAK game::symbol<char* (scr_string_t stringValue)> SL_ConvertToString{0x1405BFBB0};
}