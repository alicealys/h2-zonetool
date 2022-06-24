#include <std_include.hpp>
#include "zonetool.hpp"

namespace zonetool
{
	void dump_asset(XAsset* asset);
	void stop_dumping();

	bool verify = false;
	bool dump = false;

	filesystem::file csv_file;

	const char* get_asset_name(XAssetType type, void* pointer)
	{
		XAssetHeader header{ .data = pointer };
		XAsset xasset = { XAssetType(type), header };
		return DB_GetXAssetName(&xasset);
	}

	const char* get_asset_name(XAsset* asset)
	{
		return DB_GetXAssetName(asset);
	}

	const char* type_to_string(XAssetType type)
	{
		return g_assetNames[type];
	}

	std::int32_t type_to_int(std::string type)
	{
		for (std::int32_t i = 0; i < ASSET_TYPE_COUNT; i++)
		{
			if (g_assetNames[i] == type)
				return i;
		}

		return -1;
	}

	bool is_valid_asset_type(const std::string& type)
	{
		return type_to_int(type) >= 0;
	}

	bool zone_exists(const std::string& zone)
	{
		return DB_FileExists(zone.data(), 0);
	}

	// referenced assets
	std::vector<std::pair<XAssetType, std::string>> referencedAssets;

	bool is_referenced_asset(XAsset* asset)
	{
		if (get_asset_name(asset)[0] == ',')
		{
			return true;
		}
		return false;
	}

	XAssetHeader DB_FindXAssetHeader_Safe(XAssetType type, const std::string& name)
	{
		const auto asset_entry = DB_FindXAssetEntry(type, name.data());

		if (asset_entry)
		{
			return asset_entry->asset.header;
		}
		return DB_FindXAssetHeader(type, name.data(), 1);
	}

	void DB_EnumXAssets(const XAssetType type,
		const std::function<void(XAssetHeader)>& callback, const bool includeOverride)
	{
		DB_EnumXAssets_Internal(type, static_cast<void(*)(XAssetHeader, void*)>([](XAssetHeader header, void* data)
		{
			const auto& cb = *static_cast<const std::function<void(XAssetHeader)>*>(data);
			cb(header);
		}), &callback, includeOverride);
	}

	void dump_asset(XAsset* asset)
	{
		if (verify)
		{
			ZONETOOL_INFO("Loading asset \"%s\" of type %s.", get_asset_name(asset), type_to_string(asset->type));
		}

		// dump all
		//dump = true;
		//std::string fastfile = static_cast<std::string>(
		//	reinterpret_cast<const char*>(*reinterpret_cast<std::uintptr_t*>(0x14338E020) + 32));
		//filesystem::set_fastfile(fastfile);

		if (dump)
		{
			// open csv file for dumping 
			if (csv_file.get_fp() == nullptr)
			{
				csv_file = filesystem::file(filesystem::get_fastfile() + ".csv");
				csv_file.open("wb");
			}

			// dump assets to disk
			if (csv_file.get_fp()/* && !is_referenced_asset(xasset)*/)
			{
				fprintf(csv_file.get_fp(), "%s,%s\n", type_to_string(asset->type), get_asset_name(asset));
			}

			// check if we're done loading the zone
			if (asset->type == ASSET_TYPE_RAWFILE && get_asset_name(asset) == filesystem::get_fastfile())
			{
				stop_dumping();
			}

			// dump referenced later
			if (is_referenced_asset(asset))
			{
				//referencedAssets.push_back({ asset->type, get_asset_name(asset) });
			}
			else
			{
#define DUMP_ASSET(__type__,__interface__,__struct__) \
				if (asset->type == __type__) \
				{ \
					auto asset_ptr = reinterpret_cast<__struct__*>(asset->header.data); \
					__interface__::dump(asset_ptr); \
				}
				try
				{
					// dump assets
					DUMP_ASSET(ASSET_TYPE_DOPPLER_PRESET, IDopplerPreset, DopplerPreset);
					DUMP_ASSET(ASSET_TYPE_LOADED_SOUND, ILoadedSound, LoadedSound);
					DUMP_ASSET(ASSET_TYPE_LOCALIZE_ENTRY, ILocalize, LocalizeEntry);
					DUMP_ASSET(ASSET_TYPE_LPF_CURVE, ILpfCurve, SndCurve);
					DUMP_ASSET(ASSET_TYPE_LUA_FILE, ILuaFile, LuaFile);
					DUMP_ASSET(ASSET_TYPE_NET_CONST_STRINGS, INetConstStrings, NetConstStrings);
					DUMP_ASSET(ASSET_TYPE_RAWFILE, IRawFile, RawFile);
					DUMP_ASSET(ASSET_TYPE_REVERB_CURVE, IReverbCurve, SndCurve);
					DUMP_ASSET(ASSET_TYPE_SCRIPTFILE, IScriptFile, ScriptFile);
					DUMP_ASSET(ASSET_TYPE_SOUND, ISound, snd_alias_list_t);
					DUMP_ASSET(ASSET_TYPE_SOUND_CONTEXT, ISoundContext, SndContext);
					DUMP_ASSET(ASSET_TYPE_SOUND_CURVE, ISoundCurve, SndCurve);
					DUMP_ASSET(ASSET_TYPE_STRINGTABLE, IStringTable, StringTable);
					DUMP_ASSET(ASSET_TYPE_RAWFILE, IRawFile, RawFile);
					DUMP_ASSET(ASSET_TYPE_TTF, IFont, TTFDef);
				}
				catch (std::exception& ex)
				{
					ZONETOOL_FATAL("A fatal exception occured while dumping zone \"%s\", exception was: %s\n", filesystem::get_fastfile().data(), ex.what());
				}
			}
		}
	}

	void stop_dumping()
	{
		static bool stopping = false;
		if (stopping)
		{
			return;
		}
		stopping = true;

		if (dump)
		{
			// remove duplicates
			sort(referencedAssets.begin(), referencedAssets.end());
			referencedAssets.erase(unique(referencedAssets.begin(), referencedAssets.end()), referencedAssets.end());

			for (auto& asset : referencedAssets)
			{
				if (asset.second.length() <= 1)
				{
					continue;
				}

				const auto asset_name = &asset.second[1];

				if (asset.first == ASSET_TYPE_IMAGE)
				{
					ZONETOOL_WARNING("Not dumping referenced asset \"%s\" of type \"%s\"", asset_name, type_to_string(asset.first));
					continue;
				}

				const auto& asset_header = DB_FindXAssetHeader_Safe(asset.first, asset_name);

				if (!asset_header.data)
				{
					ZONETOOL_ERROR("Could not find referenced asset \"%s\"!", asset_name);
					continue;
				}

				//ZONETOOL_INFO("Dumping additional asset \"%s\" of type \"%s\"", asset_name, type_to_string(asset.first));

				XAsset referenced_asset = {
					asset.first,
					asset_header
				};

				dump_asset(&referenced_asset);
			}

			ZONETOOL_INFO("Zone \"%s\" dumped.", filesystem::get_fastfile().data());

			referencedAssets.clear();

			csv_file.close();
			csv_file = {};

			dump = false;
		}
		stopping = false;
	}

	utils::hook::detour DB_LinkXAssetEntry1_hook;
	XAssetEntry* DB_LinkXAssetEntry1(XAssetType type, XAssetHeader* header)
	{
		XAsset xasset = {
			type,
			*header
		};

		dump_asset(&xasset);

		return DB_LinkXAssetEntry1_hook.invoke<XAssetEntry*>(type, header);
	}

	utils::hook::detour DB_FinishLoadXFile_hook;
	void DB_FinishLoadXFile()
	{
		verify = false;
		stop_dumping();
		return DB_FinishLoadXFile_hook.invoke<void>();
	}

	void reallocate_asset_pool(const XAssetType type, const unsigned int new_size)
	{
		const size_t element_size = DB_GetXAssetTypeSize(type);

		auto* new_pool = utils::memory::get_allocator()->allocate(new_size * element_size);
		std::memmove(new_pool, g_assetPool[type], g_poolSize[type] * element_size);

		g_assetPool[type] = new_pool;
		g_poolSize[type] = new_size;
	}

	void reallocate_asset_pool_multiplier(const XAssetType type, unsigned int multiplier)
	{
		reallocate_asset_pool(type, multiplier * g_poolSize[type]);
	}

	bool load_zone(const std::string& name, DBSyncMode mode = DB_LOAD_ASYNC, bool inform = true)
	{
		if (!zone_exists(name.data()))
		{
			ZONETOOL_INFO("Zone \"%s\" could not be found!", name.data());
			return false;
		}
		if (!dump && !verify)
		{
			for (unsigned int i = 0; i < *g_zoneCount; i++)
			{
				if (!_strnicmp(g_zoneInfo[i].name, name.data(), 64))
				{
					if (inform)
					{
						ZONETOOL_INFO("zone \"%s\" is already loaded...", name.data());
					}
					return true;
				}
			}
		}
		if (inform)
		{
			ZONETOOL_INFO("Loading zone \"%s\"...", name.data());
		}

		XZoneInfo zone = { name.data(), DB_ZONE_LOAD | DB_ZONE_CUSTOM, 0 };
		DB_LoadXAssets(&zone, 1, mode);
		return true;
	}

	void unload_zones()
	{
		ZONETOOL_INFO("Unloading zones...");

		static XZoneInfo zone = { 0, DB_ZONE_NONE, 70 };
		DB_LoadXAssets(&zone, 1, DB_LOAD_ASYNC_FORCE_FREE);

		ZONETOOL_INFO("Unloaded zones...");
	}

	void dump_zone(const std::string& name)
	{
		if (!zone_exists(name.data()))
		{
			ZONETOOL_INFO("Zone \"%s\" could not be found!", name.data());
			return;
		}

		// wait for database to be ready
		while (!WaitForSingleObject(*reinterpret_cast<HANDLE*>(0x149811020), 0) == 0)
		{
			Sleep(5);
		}

		ZONETOOL_INFO("Dumping zone \"%s\"...", name.data());

		filesystem::set_fastfile(name);
		dump = true;
		if (!load_zone(name, DB_LOAD_ASYNC, false))
		{
			dump = false;
		}

		while (dump)
		{
			Sleep(1);
		}
	}

	void verify_zone(const std::string& name)
	{
		if (!zone_exists(name.data()))
		{
			ZONETOOL_INFO("Zone \"%s\" could not be found!", name.data());
			return;
		}

		// wait for database to be ready
		while (!WaitForSingleObject(*reinterpret_cast<HANDLE*>(0x149811020), 0) == 0)
		{
			Sleep(5);
		}

		verify = true;
		if (!load_zone(name, DB_LOAD_ASYNC, true))
		{
			verify = false;
		}

		while (verify)
		{
			Sleep(1);
		}
	}

	void add_assets_using_iterator(const std::string& fastfile, const std::string& type, const std::string& folder,
		const std::string& extension, bool skip_reference, IZone* zone)
	{
		if (std::filesystem::is_directory("zonetool\\" + fastfile + "\\" + folder))
		{
			for (auto& file : std::filesystem::recursive_directory_iterator(
				"zonetool\\" + fastfile + "\\" + folder))
			{
				if (is_regular_file(file))
				{
					auto filename = file.path().filename().string();

					if (skip_reference && filename[0] == ',')
					{
						// skip this file
						continue;
					}

					if (!extension.empty())
					{
						// check if the filename contains the correct extension
						if (filename.length() > extension.length() &&
							filename.substr(filename.length() - extension.length()) == extension)
						{
							// remove the extension
							filename = filename.substr(0, filename.length() - extension.length());

							// add asset to disk
							zone->add_asset_of_type(type, filename);
						}
					}
					else if (file.path().extension().empty())
					{
						// add asset to disk
						zone->add_asset_of_type(type, filename);
					}
				}
			}
		}
	}

	void parse_csv_file(IZone* zone, const std::string& fastfile, const std::string& csv)
	{
		auto path = "zone_source\\" + csv + ".csv";
		auto* parser = CsvParser_new(path.data(), ",", false);

		if (!parser)
		{
			ZONETOOL_ERROR("Could not find csv file \"%s\" to build zone!", csv.data());
			return;
		}

		auto is_referencing = false;
		auto* row = CsvParser_getRow(parser);
		while (row != nullptr)
		{
			// parse options
			if ((strlen(row->fields_[0]) >= 1 && row->fields_[0][0] == '#') || (strlen(row->fields_[0]) >= 2 && row->
				fields_[0][0] == '/' && row->fields_[0][1] == '/'))
			{
				// comment line, go to next line.
				goto nextRow;
			}
			if (!strlen(row->fields_[0]))
			{
				// empty line, go to next line.
				goto nextRow;
			}
			if (row->fields_[0] == "require"s)
			{
				load_zone(row->fields_[1], DB_LOAD_SYNC);
			}
			else if (row->fields_[0] == "include"s)
			{
				parse_csv_file(zone, fastfile, row->fields_[1]);
			}
			// this allows us to reference assets instead of rewriting them
			else if (row->fields_[0] == "reference"s)
			{
				if (row->numOfFields_ >= 2)
				{
					is_referencing = row->fields_[1] == "true"s;
				}
			}
			// this will use a directory iterator to automatically add assets
			else if (row->fields_[0] == "iterate"s)
			{
				try
				{
					add_assets_using_iterator(fastfile, "fx", "fx", ".fxe", true, zone);
					add_assets_using_iterator(fastfile, "xanimparts", "XAnim", ".xae2", true, zone);
					add_assets_using_iterator(fastfile, "xmodel", "XModel", ".xme6", true, zone);
					add_assets_using_iterator(fastfile, "material", "materials", "", true, zone);
				}
				catch (std::exception& ex)
				{
					ZONETOOL_FATAL("A fatal exception occured while building zone \"%s\", exception was: %s\n", fastfile.data(), ex.what());
				}
			}
			// if entry is not an option, it should be an asset.
			else
			{
				if (row->fields_[0] == "localize"s && row->numOfFields_ >= 2 &&
					filesystem::file("localizedstrings/"s + row->fields_[1] + ".str").exists())
				{
					ILocalize::parse_localizedstrings_file(zone, row->fields_[1]);
				}
				else
				{
					if (row->numOfFields_ >= 2)
					{
						if (is_valid_asset_type(row->fields_[0]))
						{
							try
							{
								zone->add_asset_of_type(
									row->fields_[0],
									((is_referencing) ? ","s : ""s) + row->fields_[1]
								);
							}
							catch (std::exception& ex)
							{
								ZONETOOL_FATAL("A fatal exception occured while building zone \"%s\", exception was: %s\n", fastfile.data(), ex.what());
							}
						}
					}
				}
			}

		nextRow:
			// destroy row and alloc next one.
			CsvParser_destroy_row(row);
			row = CsvParser_getRow(parser);
		}

		// free csv parser
		CsvParser_destroy(parser);
	}

	std::shared_ptr<IZone> alloc_zone(const std::string& zone)
	{
		auto ptr = std::make_shared<Zone>(zone);
		return ptr;
	}

	std::shared_ptr<ZoneBuffer> alloc_buffer()
	{
		auto ptr = std::make_shared<ZoneBuffer>();
		ptr->init_streams(7);

		return ptr;
	}

	void build_zone(const std::string& fastfile)
	{
		// make sure FS is correct.
		filesystem::set_fastfile(fastfile);

		ZONETOOL_INFO("Building fastfile \"%s\"", fastfile.data());

		auto zone = alloc_zone(fastfile);
		if (zone == nullptr)
		{
			ZONETOOL_ERROR("An error occured while building fastfile \"%s\": Are you out of memory?", fastfile.data());
			return;
		}

		parse_csv_file(zone.get(), fastfile, fastfile);

		// allocate zone buffer
		auto buffer = alloc_buffer();

		// add branding asset
		zone->add_asset_of_type("rawfile", fastfile);

		// compile zone
		zone->build(buffer.get());
	}

	void register_commands()
	{
		command::add("quit", []()
		{
			std::quick_exit(0);
		});

		command::add("buildzone", [](const command::params& params)
		{
			// Check if enough arguments have been passed to the command
			if (params.size() != 2)
			{
				ZONETOOL_ERROR("usage: buildzone <zone>");
				return;
			}

			build_zone(params.get(1));
		});

		command::add("loadzone", [](const command::params& params)
		{
			// Check if enough arguments have been passed to the command
			if (params.size() != 2)
			{
				ZONETOOL_ERROR("usage: loadzone <zone>");
				return;
			}

			load_zone(params.get(1));
		});

		command::add("unloadzones", []()
		{
			unload_zones();
		});

		command::add("dumpzone", [](const command::params& params)
		{
			// Check if enough arguments have been passed to the command
			if (params.size() != 2)
			{
				ZONETOOL_ERROR("usage: dumpzone <zone>");
				return;
			}

			dump_zone(params.get(1));
		});

		command::add("verifyzone", [](const command::params& params)
		{
			// Check if enough arguments have been passed to the command
			if (params.size() != 2)
			{
				ZONETOOL_ERROR("usage: verifyzone <zone>");
				return;
			}

			verify_zone(params.get(1));
		});
	}

	std::vector<std::string> get_command_line_arguments()
	{
		LPWSTR* szArglist;
		int nArgs;

		szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);

		std::vector<std::string> args;
		args.resize(nArgs);

		// convert all args to std::string
		for (int i = 0; i < nArgs; i++)
		{
			auto curArg = std::wstring(szArglist[i]);
			args[i] = std::string(curArg.begin(), curArg.end());
		}

		// return arguments
		return args;
	}

	void handle_params()
	{
		// Execute command line commands
		auto args = get_command_line_arguments();
		if (args.size() > 1)
		{
			for (std::size_t i = 0; i < args.size(); i++)
			{
				if (i < args.size() - 1 && i + 1 < args.size())
				{
					if (args[i] == "-buildzone")
					{
						build_zone(args[i + 1]);
						i++;
					}
					else if (args[i] == "-loadzone")
					{
						load_zone(args[i + 1]);
						i++;
					}
					else if (args[i] == "-dumpzone")
					{
						dump_zone(args[i + 1]);
						i++;
					}
				}
			}

			std::quick_exit(0);
		}
	}

	void branding()
	{
		ZONETOOL_INFO("ZoneTool initialization complete!");
		ZONETOOL_INFO("No matter how hard or unlikely, if it's possible, it will be done.");
		ZONETOOL_INFO("Special thanks to: RektInator, Laupetin, NTAuthority, momo5502, TheApadayo, localhost, X3RX35 & homura.");
	}

	void on_exit(void)
	{
		dump = false;
		csv_file.close();
	}

	utils::hook::detour doexit_hook;
	void doexit(unsigned int a1, int a2, int a3)
	{
		on_exit();
		doexit_hook.invoke<void>(a1, a2, a3);
		//std::quick_exit(0);
	}

	void init_zonetool()
	{
		static bool initialized = false;
		if (initialized) return;
		initialized = true;

		ZONETOOL_INFO("ZoneTool is initializing...");

		// reallocs
		reallocate_asset_pool_multiplier(ASSET_TYPE_LUA_FILE, 2);
		reallocate_asset_pool_multiplier(ASSET_TYPE_WEAPON, 2);
		reallocate_asset_pool_multiplier(ASSET_TYPE_LOCALIZE_ENTRY, 2);
		reallocate_asset_pool_multiplier(ASSET_TYPE_XANIM, 2);
		reallocate_asset_pool_multiplier(ASSET_TYPE_ATTACHMENT, 2);
		reallocate_asset_pool_multiplier(ASSET_TYPE_TTF, 2);
		reallocate_asset_pool_multiplier(ASSET_TYPE_SNDDRIVERGLOBALS, 4);
		reallocate_asset_pool_multiplier(ASSET_TYPE_EQUIPMENT_SND_TABLE, 4);
		reallocate_asset_pool_multiplier(ASSET_TYPE_SOUND, 2);
		reallocate_asset_pool_multiplier(ASSET_TYPE_LOADED_SOUND, 2);
		reallocate_asset_pool_multiplier(ASSET_TYPE_LEADERBOARDDEF, 2);
		reallocate_asset_pool_multiplier(ASSET_TYPE_VERTEXDECL, 6);
		reallocate_asset_pool_multiplier(ASSET_TYPE_COMPUTESHADER, 4);
		reallocate_asset_pool_multiplier(ASSET_TYPE_REVERB_PRESET, 2);

		// enable dumping
		DB_LinkXAssetEntry1_hook.create(0x1402BC920, &DB_LinkXAssetEntry1);

		// stop dumping
		DB_FinishLoadXFile_hook.create(0x14028DC30, &DB_FinishLoadXFile);

		doexit_hook.create(0x1407948E0, doexit);
		atexit(on_exit);
	}

	void initialize()
	{
		init_zonetool();
	}

	void start()
	{
		initialize();

		branding();
		register_commands();

		handle_params();
	}
}