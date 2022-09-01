#include <std_include.hpp>
#include "mapents.hpp"

namespace zonetool
{
	namespace
	{
		std::unordered_map<std::string, unsigned> token_map =
		{
			// built-in entity fields
			{"code_classname", 172},
			{"classname", 170},
			{"model", 669},
			{"count", 216},
			{"health", 486},
			{"dmg", 293},
			{"maxhealth", 626},
			{"anglelerprate", 64},
			{"activator", 19},
			{"slidevelocity", 974},
			{"disableplayeradsloscheck", 291},
			{"accuracy", 10},
			{"lookforward", 604},
			{"lookright", 605},
			{"lookup", 607},
			{"fovcosine", 411},
			{"fovcosinebusy", 412},
			{"fovcosinez", 413},
			{"upaimlimit", 1252},
			{"downaimlimit", 307},
			{"rightaimlimit", 894},
			{"leftaimlimit", 590},
			{"maxsightdistsqrd", 628},
			{"sightlatency", 967},
			{"defaultsightlatency", 968},
			{"ignoreclosefoliage", 508},
			{"interval", 525},
			{"teammovewaittime", 1199},
			{"damagetaken", 257},
			{"damagedir", 252},
			{"damageyaw", 259},
			{"damagelocation", 253},
			{"damageweapon", 258},
			{"damagemod", 254},
			{"proneok", 841},
			{"walkdistfacingmotion", 1299},
			{"walkdist", 1298},
			{"desiredangle", 278},
			{"pacifist", 744},
			{"pacifistwait", 745},
			{"footstepdetectdist", 398},
			{"footstepdetectdistwalk", 400},
			{"footstepdetectdistsprint", 399},
			{"reactiontargetpos", 859},
			{"newenemyreactiondistsq", 686},
			{"ignoreexplosionevents", 509},
			{"ignoresuppression", 513},
			{"suppressionwait", 1060},
			{"suppressionduration", 1056},
			{"suppressionstarttime", 1058},
			{"suppressionmeter", 1057},
			{"ignoreplayersuppression", 514},
			{"name", 680},
			{"weapon", 1302},
			{"dontavoidplayer", 304},
			{"grenadeawareness", 465},
			{"grenade", 458},
			{"grenadeweapon", 470},
			{"grenadeammo", 464},
			{"grenadetargetpos", 467},
			{"grenadetargetvalid", 468},
			{"grenadetossvel", 469},
			{"favoriteenemy", 377},
			{"highlyawareradius", 495},
			{"minpaindamage", 642},
			{"allowpain", 52},
			{"allowdeath", 49},
			{"delayeddeath", 274},
			{"diequietly", 287},
			{"forceragdollimmediate", 405},
			{"providecoveringfire", 842},
			{"doingambush", 302},
			{"combatmode", 199},
			{"alertlevel", 38},
			{"alertlevelint", 39},
			{"useable", 1257},
			{"ignoretriggers", 515},
			{"pushable", 846},
			{"script_pushable", 926},
			{"dropweapon", 309},
			{"drawoncompass", 308},
			{"groundtype", 474},
			{"anim_pose", 68},
			{"goalradius", 452},
			{"goalheight", 450},
			{"goalpos", 451},
			{"nodeoffsetpos", 705},
			{"ignoreforfixednodesafecheck", 510},
			{"fixednode", 381},
			{"fixednodesaferadius", 382},
			{"pathgoalpos", 762},
			{"pathrandompercent", 764},
			{"usechokepoints", 1258},
			{"stopanimdistsq", 1044},
			{"lastenemysightpos", 584},
			{"pathenemylookahead", 761},
			{"pathenemyfightdist", 760},
			{"meleeattackdist", 633},
			{"movemode", 675},
			{"script_move_distance_override", 31298},
			{"usecombatscriptatcover", 1259},
			{"safetochangescript", 906},
			{"keepclaimednode", 561},
			{"keepclaimednodeifvalid", 562},
			{"keepnodeduringscriptedanim", 563},
			{"dodangerreact", 295},
			{"dangerreactduration", 260},
			{"nododgemove", 706},
			{"noteammove", 707},
			{"leanamount", 587},
			{"pitchamount", 788},
			{"turnrate", 1230},
			{"turnanimactive", 1229},
			{"badplaceawareness", 107},
			{"damageshield", 256},
			{"nogrenadereturnthrow", 709},
			{"noattackeraccuracymod", 698},
			{"frontshieldanglecos", 426},
			{"lookaheaddir", 601},
			{"lookaheaddist", 602},
			{"lookaheadhitsstairs", 603},
			{"velocity", 1283},
			{"prevanimdelta", 821},
			{"exposedduration", 356},
			{"requestarrivalnotify", 875},
			{"scriptedarrivalent", 938},
			{"goingtoruntopos", 455},
			{"engagemindist", 334},
			{"engageminfalloffdist", 335},
			{"engagemaxdist", 332},
			{"engagemaxfalloffdist", 333},
			{"usingcovermoveup", 42987},
			{"finalaccuracy", 378},
			{"facemotion", 373},
			{"gunblockedbywall", 475},
			{"relativedir", 866},
			{"lockorientation", 597},
			{"maxfaceenemydist", 625},
			{"stairsstate", 1012},
			{"script", 912},
			{"prevscript", 823},
			{"headicon", 483},
			{"headiconteam", 484},
			{"coversearchinterval", 219},
			{"threatupdateinterval", 37018},
			{"canclimbladders", 150},
			{"swimmer", 1063},
			{"space", 986},
			{"doghandler", 301},
			{"sharpturnlookaheaddist", 961},
			{"postsharpturnlookaheaddist", 813},
			{"sharpturntooclosetodestdist", 963},
			{"usepathsmoothingvalues", 1262},
			{"pathlookaheaddist", 763},
			{"maxturnspeed", 629},
			{"sharpturn", 960},
			{"disablesightandthreatupdate", 54743},
			{"team", 1194},
			{"threatbias", 1204},
			{"threatbiasgroup", 1205},
			{"node", 700},
			{"prevnode", 822},
			{"enemy", 322},
			{"syncedmeleetarget", 1065},
			{"lastattacker", 583},
			{"lastpusher", 42997},
			{"ignoreme", 511},
			{"ignoreall", 507},
			{"maxvisibledist", 630},
			{"surprisedbymedistsq", 1062},
			{"attackeraccuracy", 86},
			{"ignorerandombulletdamage", 512},
			{"dodamagetoall", 294},
			{"turretinvulnerability", 1240},
			{"useorcaavoidance", 1261},
			{"reciprocality", 863},
			{"avoidanceboundshalfsize", 94},
			{"onlygoodnearestnodes", 735},
			{"playername", 803},
			{"deathinvulnerabletime", 266},
			{"criticalbulletdamagedist", 222},
			{"attackercount", 87},
			{"damagemultiplier", 255},
			{"laststand", 586},
			{"motiontrackerenabled", 672},
			{"veh_speed", 1276},
			{"veh_pathspeed", 1273},
			{"veh_transmission", 1279},
			{"veh_pathdir", 1272},
			{"veh_pathtype", 1274},
			{"veh_topspeed", 1278},
			{"veh_brake", 1266},
			{"veh_throttle", 1277},
			{"x", 1331},
			{"y", 1339},
			{"z", 1342},
			{"fontscale", 393},
			{"font", 392},
			{"alignx", 44},
			{"aligny", 45},
			{"horzalign", 499},
			{"vertalign", 1284},
			{"color", 196},
			{"alpha", 55},
			{"label", 578},
			{"sort", 983},
			{"foreground", 408},
			{"lowresbackground", 612},
			{"hidewhendead", 491},
			{"hidewheninmenu", 493},
			{"glowcolor", 445},
			{"glowalpha", 444},
			{"positioninworld", 812},
			{"relativeoffset", 867},
			{"enablehudlighting", 315},
			{"enableinputprogressicon", 42996},
			{"rotation", 902},
			{"targetname", 1193},
			{"target", 1191},
			{"animscript", 71},
			{"script_linkname", 920},
			{"script_noteworthy", 922},
			{"origin", 740},
			{"angles", 65},
			{"minusedistsq", 643},
			{"parentname", 749},
			{"spawnflags", 989},
			{"type", 1244},
			{"owner", 743},
			{"radius", 851},
			{"customangles", 9555},
			{"speed", 997},
			{"lookahead", 600},

			// mapent keys
			{"code_classname", 172},
			{"classname", 170},
			{"origin", 740},
			{"model", 669},
			{"spawnflags", 989},
			{"target", 1191},
			{"targetname", 1193},
			{"count", 216},
			{"rotation", 902},
			{"animscript", 71},
			{"script_linkname", 920},
			{"script_noteworthy", 922},
			{"angles", 65},
			{"parentname", 749},
			{"type", 1244},
			{"owner", 743},
			{"radius", 851},
			{"height", 488},
			{"customangles", 9555},
			{"speed", 997},
			{"lookahead", 600},

			{"_color", 1398},
			{"skycolor", 34255},
			{"suncolor", 1049},
			{"sundirection", 1050},
			{"modelscale", 23881},
			{"export", 13703},
			{"animation", 70},
			{"spammed_model", 49508},
			{"vehicletype", 1282},

			{"script_flag", 31190},
			{"script_flag_true", 31196},
			{"script_stealth_function", 31462},
			{"script_stealth", 31460},
			{"script_deathflag", 31114},
			{"script_forcespawn", 31214},
			{"script_stealthgroup", 31463},
			{"script_delay", 916},
			{"script_color_allies", 31096},
			{"script_patroller", 31391},
			{"script_idlereach", 31253},
			{"script_linkto", 31273},
			{"script_animation", 31039},
			{"script_startinghealth", 31454},
			{"script_pet", 9},
			{"script_goalheight", 31236},
			{"script_parameters", 31388},
			{"script_combatmode", 31102},
			{"script_ammo_clip", 31034},
			{"script_moveoverride", 31299},
			{"script_forcegoal", 31212},
			{"script_ammo_max", 31036},
			{"script_vehicleride", 31516},
			{"script_idleanim", 31252},
			{"script_chatgroup", 31092},
			{"script_vehicle_anim", 40318},
			{"script_vehicledetour", 31510},
			{"script_vehiclegroupdelete", 31514},
			{"script_flag_wait", 31197},
			{"script_emptyspawner", 31161},
			{"script_aigroup", 31025},
			{"script_group", 31245},
			{"script_index", 31259},
			{"script_delay_post", 31122},
			{"script_killspawner", 31264},
			{"script_goalvolume", 31238},
			{"script_drone", 31152},
			{"script_health", 31247},
			{"script_friendname", 31217},
			{"script_airspeed", 31027},
			{"script_missiles", 31293},
			{"script_spotlight", 31447},
			{"script_team", 31474},
			{"script_ai_invulnerable", 31024},
			{"script_mp_style_helicopter", 31353},
			{"script_startingposition", 31455},
			{"script_vehicle_selfremove", 31507},
			{"script_stopnode", 31464},
			{"script_unload", 31497},

			{"script_specialops", 0xEFFF}, // custom, defined in h2-mod/src/client/component/mapents.cpp
		};

		std::string convert_mapents(const std::string& source)
		{
			std::string out_buffer{};
			const auto lines = utils::string::split(source, '\n');

			bool in_map_ent = false;
			bool empty = false;
			int line_index{};
			for (const auto& line : lines)
			{
				const auto _0 = gsl::finally([&]()
				{
					line_index++;
				});

				if (line[0] == '{' && !in_map_ent)
				{
					in_map_ent = true;
					out_buffer.append("{\n");
					continue;
				}

				if (line[0] == '{' && in_map_ent)
				{
					throw std::runtime_error(utils::string::va("[addon_map_ents parser] '{' on line %i\n", line_index));
				}

				if (line[0] == '}' && in_map_ent)
				{
					if (empty)
					{
						out_buffer.append("\n}\n");
					}
					else if (line_index < static_cast<int>(lines.size()) - 1)
					{
						out_buffer.append("}\n");
					}
					else
					{
						out_buffer.append("}\0");
					}

					in_map_ent = false;
					continue;
				}

				if (line[0] == '}' && !in_map_ent)
				{
					throw std::runtime_error(utils::string::va("[addon_map_ents parser] Unexpected '}' on line %i\n", line_index));
				}

				std::regex expr(R"~((.+) "(.*)")~");
				std::smatch match{};
				if (!std::regex_search(line, match, expr))
				{
					printf("[addon_map_ents parser] Failed to parse line %i\n", line_index);
					continue;
				}

				auto key = utils::string::to_lower(match[1].str());
				const auto value = match[2].str();

				if (key.size() <= 0 || value.size() <= 0)
				{
					printf("[addon_map_ents parser] Invalid key/value ('%s' '%s') pair on line %i\n", key.data(), value.data(), line_index);
					continue;
				}

				empty = false;

				auto key_id = std::atoi(key.data());
				if (key_id != 0)
				{
					out_buffer.append(utils::string::va("%i \"%s\"\n", key_id, value.data()));
					continue;
				}

				if (key.size() < 3 || (!key.starts_with("\"") || !key.ends_with("\"")))
				{
					printf("[addon_map_ents parser] Bad key '%s' on line %i\n", key.data(), line_index);
					continue;
				}

				const auto key_ = key.substr(1, key.size() - 2);
				if (token_map.find(key_) == token_map.end())
				{
					printf("[addon_map_ents parser] Key '%s' not found, on line %i\n", key_.data(), line_index);
					continue;
				}

				out_buffer.append(utils::string::va("%i \"%s\"\n", token_map[key_], value.data()));
			}

			return out_buffer;
		}

	}

	void IMapEnts::convert_ents(MapEnts* ents, ZoneMemory* mem)
	{
		const auto str = convert_mapents(ents->entityString);
		ents->entityString = mem->StrDup(str);
		ents->numEntityChars = static_cast<int>(str.size());
	}

	void IMapEnts::add_script_string(scr_string_t* ptr, std::string str)
	{
		for (std::uint32_t i = 0; i < this->script_strings.size(); i++)
		{
			if (this->script_strings[i].first == ptr)
			{
				return;
			}
		}
		this->script_strings.push_back(std::pair<scr_string_t*, std::string>(ptr, str));
	}

	std::string IMapEnts::get_script_string(scr_string_t* ptr)
	{
		for (std::uint32_t i = 0; i < this->script_strings.size(); i++)
		{
			if (this->script_strings[i].first == ptr)
			{
				return this->script_strings[i].second;
			}
		}
		return "";
	}

	void IMapEnts::parse_splineList(ZoneMemory* mem, std::string name, SplineRecordList* splineList)
	{
		assetmanager::reader reader(mem);
		const auto path = name + ".ents.splineList"s;
		if (reader.open(path))
		{
			splineList->splineCount = reader.read_short();
			splineList->splines = reader.read_array<SplinePointRecordList>();
			for (unsigned short i = 0; i < splineList->splineCount; i++)
			{
				splineList->splines[i].splinePoints = reader.read_array<SplinePointEntityRecord>();
				for (unsigned short j = 0; j < splineList->splines[i].splinePointCount; j++)
				{
					splineList->splines[i].splinePoints[j].splineNodeLabel = reader.read_array<char>();
					splineList->splines[i].splinePoints[j].positionCubic = reader.read_array<vec3_t>();
					splineList->splines[i].splinePoints[j].tangentQuadratic = reader.read_array<vec3_t>();
				}
			}

			reader.close();
		}
	}

	void IMapEnts::parse_spawnList(ZoneMemory* mem, std::string name, SpawnPointRecordList* spawnList)
	{
		const auto path = name + ".ents.spawnList"s;
		filesystem::file file(path);
		file.open("rb");
		if (!file.get_fp())
		{
			return;
		}

		const auto size = file.size();
		auto bytes = file.read_bytes(size);
		file.close();

		auto data = json::parse(bytes);

		spawnList->spawnsCount = static_cast<unsigned short>(data.size());
		spawnList->spawns = mem->Alloc<SpawnPointEntityRecord>(spawnList->spawnsCount);

		for (unsigned short i = 0; i < spawnList->spawnsCount; i++)
		{
			spawnList->spawns[i].index = i;
			add_script_string(&spawnList->spawns[i].name, data[i]["name"].get<std::string>());
			add_script_string(&spawnList->spawns[i].target, data[i]["target"].get<std::string>());
			add_script_string(&spawnList->spawns[i].script_noteworthy, data[i]["script_noteworthy"].get<std::string>());
			add_script_string(&spawnList->spawns[i].unknown, data[i]["script_noteworthy"].get<std::string>());
			for (auto j = 0; j < 3; j++)
			{
				spawnList->spawns[i].origin[j] = data[i]["origin"][j].get<float>();
				spawnList->spawns[i].angles[j] = data[i]["angles"][j].get<float>();
			}
		}
	}

	void IMapEnts::parse_clientBlendTriggers(ZoneMemory* mem, std::string name, ClientTriggerBlend* clientTriggerBlend)
	{
		assetmanager::reader reader(mem);
		const auto path = name + ".ents.clientBlendTriggers"s;
		if (reader.open(path))
		{
			clientTriggerBlend->numClientTriggerBlendNodes = reader.read_short();
			clientTriggerBlend->blendNodes = reader.read_array<ClientTriggerBlendNode>();

			reader.close();
		}
	}

	void IMapEnts::parse_clientTriggers(ZoneMemory* mem, std::string name, ClientTriggers* clientTrigger)
	{
		assetmanager::reader reader(mem);
		const auto path = name + ".ents.clientTriggers";
		if (reader.open(path))
		{
			clientTrigger->trigger.count = reader.read_int();
			clientTrigger->trigger.models = reader.read_array<TriggerModel>();

			clientTrigger->trigger.hullCount = reader.read_int();
			clientTrigger->trigger.hulls = reader.read_array<TriggerHull>();

			clientTrigger->trigger.slabCount = reader.read_int();
			clientTrigger->trigger.slabs = reader.read_array<TriggerSlab>();

			clientTrigger->clientTriggerAabbTree = reader.read_array<ClientTriggerAabbNode>();

			clientTrigger->triggerStringLength = reader.read_int();
			clientTrigger->triggerString = reader.read_array<char>();

			clientTrigger->unk0 = reader.read_array<short>();
			clientTrigger->unk1 = reader.read_array<short>();
			clientTrigger->unk2 = reader.read_array<short>();
			clientTrigger->triggerType = reader.read_array<short>();
			clientTrigger->origins = reader.read_array<vec3_t>();
			clientTrigger->scriptDelay = reader.read_array<float>();
			clientTrigger->unk3 = reader.read_array<short>();
			clientTrigger->unk4 = reader.read_array<short>();
			clientTrigger->unk5 = reader.read_array<short>();
			clientTrigger->unk6 = reader.read_array<short>();
			clientTrigger->unk7 = reader.read_array<short>();
			clientTrigger->unk8 = reader.read_array<short>();

			reader.close();
		}
	}

	void IMapEnts::parse_triggers(ZoneMemory* mem, std::string name, MapTriggers* trigger)
	{
		assetmanager::reader reader(mem);
		const auto path = name + ".ents.triggers"s;
		if (reader.open(path))
		{
			trigger->count = reader.read_int();
			trigger->models = reader.read_array<TriggerModel>();

			trigger->hullCount = reader.read_int();
			trigger->hulls = reader.read_array<TriggerHull>();

			trigger->slabCount = reader.read_int();
			trigger->slabs = reader.read_array<TriggerSlab>();

			reader.close();
		}
	}

	void IMapEnts::parse_entityStrings(ZoneMemory* mem, std::string name, char** entityStrings, int* numEntityChars)
	{
		const auto path = name + ".ents"s;
		auto file = filesystem::file(path);
		file.open("rb");
		if (!file.get_fp())
		{
			return;
		}

		*numEntityChars = static_cast<int>(file.size());

		*entityStrings = mem->Alloc<char>(static_cast<size_t>(*numEntityChars + 1));
		memset(*entityStrings, 0, *numEntityChars);

		fread(*entityStrings, *numEntityChars, 1, file.get_fp());
		(*entityStrings)[*numEntityChars] = '\0';

		file.close();
	}

	MapEnts* IMapEnts::parse(std::string name, ZoneMemory* mem)
	{
		const auto path = name + ".ents"s;
		if (!filesystem::file(path).exists())
		{
			return nullptr;
		}

		ZONETOOL_INFO("Parsing mapents \"%s\"...", name.data());

		MapEnts* ents = mem->Alloc<MapEnts>();
		ents->name = mem->StrDup(name);

		parse_entityStrings(mem, name, &ents->entityString, &ents->numEntityChars);
		convert_ents(ents, mem);

		parse_triggers(mem, name, &ents->trigger);
		parse_clientTriggers(mem, name, &ents->clientTrigger);
		parse_clientBlendTriggers(mem, name, &ents->clientTriggerBlend);
		parse_spawnList(mem, name, &ents->spawnList);
		parse_splineList(mem, name, &ents->splineList);

		return ents;
	}

	void IMapEnts::init(const std::string& name, ZoneMemory* mem)
	{
		this->name_ = "maps/"s + (filesystem::get_fastfile().substr(0, 3) == "mp_" ? "mp/" : "") + filesystem::get_fastfile() + ".d3dbsp"; // name;

		if (this->referenced())
		{
			this->asset_ = mem->Alloc<typename std::remove_reference<decltype(*this->asset_)>::type>();
			this->asset_->name = mem->StrDup(name);
			return;
		}

		this->asset_ = this->parse(name, mem);
		if (!this->asset_)
		{
			ZONETOOL_FATAL("Could not find mapents: \"%s\"", this->name_.data());
		}
	}

	void IMapEnts::prepare(ZoneBuffer* buf, ZoneMemory* mem)
	{
		auto* data = this->asset_;

		if (data->spawnList.spawns)
		{
			for (int i = 0; i < data->spawnList.spawnsCount; i++)
			{
				std::string str = this->get_script_string(&data->spawnList.spawns[i].name);
				data->spawnList.spawns[i].name = static_cast<scr_string_t>(buf->write_scriptstring(str));

				str = this->get_script_string(&data->spawnList.spawns[i].target);
				data->spawnList.spawns[i].target = static_cast<scr_string_t>(buf->write_scriptstring(str));

				str = this->get_script_string(&data->spawnList.spawns[i].script_noteworthy);
				data->spawnList.spawns[i].script_noteworthy = static_cast<scr_string_t>(buf->write_scriptstring(str));

				str = this->get_script_string(&data->spawnList.spawns[i].unknown);
				data->spawnList.spawns[i].unknown = static_cast<scr_string_t>(buf->write_scriptstring(str));
			}
		}
	}

	void IMapEnts::load_depending(IZone* zone)
	{
	}

	std::string IMapEnts::name()
	{
		return this->name_;
	}

	std::int32_t IMapEnts::type()
	{
		return ASSET_TYPE_MAP_ENTS;
	}

	void IMapEnts::write_triggers(ZoneBuffer* buf, MapTriggers* dest)
	{
		if (dest->models)
		{
			dest->models = buf->write_s(3, dest->models, dest->count);
		}

		if (dest->hulls)
		{
			dest->hulls = buf->write_s(3, dest->hulls, dest->hullCount);
		}

		if (dest->slabs)
		{
			dest->slabs = buf->write_s(3, dest->slabs, dest->slabCount);
		}
	}

	void IMapEnts::write(IZone* zone, ZoneBuffer* buf)
	{
		auto* data = this->asset_;
		auto* dest = buf->write(data);

		buf->push_stream(3);

		dest->name = buf->write_str(this->name());

		if (data->entityString)
		{
			buf->align(0);
			buf->write(data->entityString, data->numEntityChars);
			ZoneBuffer::clear_pointer(&dest->entityString);
		}

		write_triggers(buf, &dest->trigger);
		write_triggers(buf, &dest->clientTrigger.trigger);

		if (data->clientTrigger.clientTriggerAabbTree)
		{
			buf->align(3);
			buf->write(data->clientTrigger.clientTriggerAabbTree, data->clientTrigger.numClientTriggerNodes);
			ZoneBuffer::clear_pointer(&dest->clientTrigger.clientTriggerAabbTree);
		}
		if (data->clientTrigger.triggerString)
		{
			buf->align(0);
			buf->write(data->clientTrigger.triggerString, data->clientTrigger.triggerStringLength);
			ZoneBuffer::clear_pointer(&dest->clientTrigger.triggerString);
		}
		if (data->clientTrigger.unk0)
		{
			buf->align(1);
			buf->write(data->clientTrigger.unk0, data->clientTrigger.trigger.count);
			ZoneBuffer::clear_pointer(&dest->clientTrigger.unk0);
		}
		if (data->clientTrigger.unk1)
		{
			buf->align(1);
			buf->write(data->clientTrigger.unk1, data->clientTrigger.trigger.count);
			ZoneBuffer::clear_pointer(&dest->clientTrigger.unk1);
		}
		if (data->clientTrigger.unk2)
		{
			buf->align(1);
			buf->write(data->clientTrigger.unk2, data->clientTrigger.trigger.count);
			ZoneBuffer::clear_pointer(&dest->clientTrigger.unk2);
		}
		if (data->clientTrigger.triggerType)
		{
			buf->align(1);
			buf->write(data->clientTrigger.triggerType, data->clientTrigger.trigger.count);
			ZoneBuffer::clear_pointer(&dest->clientTrigger.triggerType);
		}
		if (data->clientTrigger.origins)
		{
			buf->align(3);
			buf->write(data->clientTrigger.origins, data->clientTrigger.trigger.count);
			ZoneBuffer::clear_pointer(&dest->clientTrigger.origins);
		}
		if (data->clientTrigger.scriptDelay)
		{
			buf->align(3);
			buf->write(data->clientTrigger.scriptDelay, data->clientTrigger.trigger.count);
			ZoneBuffer::clear_pointer(&dest->clientTrigger.scriptDelay);
		}
		if (data->clientTrigger.unk3)
		{
			buf->align(1);
			buf->write(data->clientTrigger.unk3, data->clientTrigger.trigger.count);
			ZoneBuffer::clear_pointer(&dest->clientTrigger.unk3);
		}
		if (data->clientTrigger.unk4)
		{
			buf->align(1);
			buf->write(data->clientTrigger.unk4, data->clientTrigger.trigger.count);
			ZoneBuffer::clear_pointer(&dest->clientTrigger.unk4);
		}
		if (data->clientTrigger.unk5)
		{
			buf->align(1);
			buf->write(data->clientTrigger.unk5, data->clientTrigger.trigger.count);
			ZoneBuffer::clear_pointer(&dest->clientTrigger.unk5);
		}
		if (data->clientTrigger.unk6)
		{
			buf->align(1);
			buf->write(data->clientTrigger.unk6, data->clientTrigger.trigger.count);
			ZoneBuffer::clear_pointer(&dest->clientTrigger.unk6);
		}
		if (data->clientTrigger.unk7)
		{
			buf->align(1);
			buf->write(data->clientTrigger.unk7, data->clientTrigger.trigger.count);
			ZoneBuffer::clear_pointer(&dest->clientTrigger.unk7);
		}
		if (data->clientTrigger.unk8)
		{
			buf->align(1);
			buf->write(data->clientTrigger.unk8, data->clientTrigger.trigger.count);
			ZoneBuffer::clear_pointer(&dest->clientTrigger.unk8);
		}

		if (data->clientTriggerBlend.blendNodes)
		{
			buf->align(3);
			buf->write(data->clientTriggerBlend.blendNodes, data->clientTriggerBlend.numClientTriggerBlendNodes);
			ZoneBuffer::clear_pointer(&dest->clientTriggerBlend.blendNodes);
		}

		if (data->spawnList.spawns)
		{
			buf->align(3);
			buf->write(data->spawnList.spawns, data->spawnList.spawnsCount);
			ZoneBuffer::clear_pointer(&dest->spawnList.spawns);
		}

		if (data->splineList.splines)
		{
			buf->align(3);
			auto destsplines = buf->write(data->splineList.splines, data->splineList.splineCount);
			for (unsigned short i = 0; i < data->splineList.splineCount; i++)
			{
				if (data->splineList.splines[i].splinePoints)
				{
					buf->align(3);
					auto destsplinepoints = buf->write(data->splineList.splines[i].splinePoints,
						data->splineList.splines[i].splinePointCount);
					for (unsigned short j = 0; j < data->splineList.splines[i].splinePointCount; j++)
					{
						if (data->splineList.splines[i].splinePoints[j].splineNodeLabel)
						{
							buf->align(0);
							buf->write(data->splineList.splines[i].splinePoints[j].splineNodeLabel, 64);
							ZoneBuffer::clear_pointer(destsplinepoints[j].splineNodeLabel);
						}
						if (data->splineList.splines[i].splinePoints[j].positionCubic)
						{
							buf->align(3);
							buf->write(data->splineList.splines[i].splinePoints[j].positionCubic, 48);
							ZoneBuffer::clear_pointer(&destsplinepoints[j].positionCubic);
						}
						if (data->splineList.splines[i].splinePoints[j].tangentQuadratic)
						{
							buf->align(3);
							buf->write(data->splineList.splines[i].splinePoints[j].tangentQuadratic, 36);
							ZoneBuffer::clear_pointer(&destsplinepoints[j].tangentQuadratic);
						}
					}
					ZoneBuffer::clear_pointer(&destsplines->splinePoints);
				}
			}
			ZoneBuffer::clear_pointer(&dest->splineList.splines);
		}

		buf->pop_stream();
	}

	void IMapEnts::dump_splineList(const std::string& name, SplineRecordList* splineList)
	{
		assetmanager::dumper dumper;
		const auto path = name + ".ents.splineList"s;
		if (dumper.open(path))
		{
			dumper.dump_short(splineList->splineCount);
			dumper.dump_array(splineList->splines, splineList->splineCount);
			for (unsigned short i = 0; i < splineList->splineCount; i++)
			{
				dumper.dump_array(splineList->splines[i].splinePoints, splineList->splines[i].splinePointCount);
				for (unsigned short j = 0; j < splineList->splines[i].splinePointCount; j++)
				{
					dumper.dump_array(splineList->splines[i].splinePoints[j].splineNodeLabel, 64);
					dumper.dump_array(splineList->splines[i].splinePoints[j].positionCubic, 48);
					dumper.dump_array(splineList->splines[i].splinePoints[j].tangentQuadratic, 36);
				}
			}
		}
	}

	void IMapEnts::dump_spawnList(const std::string& name, SpawnPointRecordList* spawnList)
	{
		const auto path = name + ".ents.spawnList"s;
		auto file = filesystem::file(path);
		file.open("wb");

		if (!file.get_fp())
		{
			return;
		}

		ordered_json data;

		for (unsigned short i = 0; i < spawnList->spawnsCount; i++)
		{
			data[i]["name"] = SL_ConvertToString(spawnList->spawns[i].name);
			data[i]["target"] = SL_ConvertToString(spawnList->spawns[i].target);
			data[i]["script_noteworthy"] = SL_ConvertToString(spawnList->spawns[i].script_noteworthy);
			data[i]["unknown"] = SL_ConvertToString(spawnList->spawns[i].unknown);
			for (auto j = 0; j < 3; j++)
			{
				data[i]["origin"][j] = spawnList->spawns[i].origin[j];
				data[i]["angles"][j] = spawnList->spawns[i].angles[j];
			}
		}

		const auto json = data.dump(4);
		file.write(json.data(), json.size(), 1);

		file.close();
	}

	void IMapEnts::dump_clientBlendTriggers(const std::string& name, ClientTriggerBlend* clientTriggerBlend)
	{
		assetmanager::dumper dumper;
		const auto path = name + ".ents.clientBlendTriggers"s;
		if (dumper.open(path))
		{
			dumper.dump_short(clientTriggerBlend->numClientTriggerBlendNodes);
			dumper.dump_array(clientTriggerBlend->blendNodes, clientTriggerBlend->numClientTriggerBlendNodes);
		}
	}

	void IMapEnts::dump_clientTriggers(const std::string& name, ClientTriggers* clientTrigger)
	{
		assetmanager::dumper dumper;
		const auto path = name + ".ents.clientTriggers";
		if (dumper.open(path))
		{
			dumper.dump_int(clientTrigger->trigger.count);
			dumper.dump_array<TriggerModel>(clientTrigger->trigger.models, clientTrigger->trigger.count);

			dumper.dump_int(clientTrigger->trigger.hullCount);
			dumper.dump_array<TriggerHull>(clientTrigger->trigger.hulls, clientTrigger->trigger.hullCount);

			dumper.dump_int(clientTrigger->trigger.slabCount);
			dumper.dump_array<TriggerSlab>(clientTrigger->trigger.slabs, clientTrigger->trigger.slabCount);

			dumper.dump_array(clientTrigger->clientTriggerAabbTree, clientTrigger->numClientTriggerNodes);

			dumper.dump_int(clientTrigger->triggerStringLength);
			dumper.dump_array(clientTrigger->triggerString, clientTrigger->triggerStringLength);

			dumper.dump_array(clientTrigger->unk0, clientTrigger->trigger.count);
			dumper.dump_array(clientTrigger->unk1, clientTrigger->trigger.count);
			dumper.dump_array(clientTrigger->unk2, clientTrigger->trigger.count);
			dumper.dump_array(clientTrigger->triggerType, clientTrigger->trigger.count);
			dumper.dump_array(clientTrigger->origins, clientTrigger->trigger.count);
			dumper.dump_array(clientTrigger->scriptDelay, clientTrigger->trigger.count);
			dumper.dump_array(clientTrigger->unk3, clientTrigger->trigger.count);
			dumper.dump_array(clientTrigger->unk4, clientTrigger->trigger.count);
			dumper.dump_array(clientTrigger->unk5, clientTrigger->trigger.count);
			dumper.dump_array(clientTrigger->unk6, clientTrigger->trigger.count);
			dumper.dump_array(clientTrigger->unk7, clientTrigger->trigger.count);
			dumper.dump_array(clientTrigger->unk8, clientTrigger->trigger.count);

			dumper.close();
		}
	}

	void IMapEnts::dump_triggers(const std::string& name, MapTriggers* trigger)
	{
		assetmanager::dumper dumper;
		const auto path = name + ".ents.triggers"s;
		if (dumper.open(path))
		{
			dumper.dump_int(trigger->count);
			dumper.dump_array<TriggerModel>(trigger->models, trigger->count);

			dumper.dump_int(trigger->hullCount);
			dumper.dump_array<TriggerHull>(trigger->hulls, trigger->hullCount);

			dumper.dump_int(trigger->slabCount);
			dumper.dump_array<TriggerSlab>(trigger->slabs, trigger->slabCount);

			dumper.close();
		}
	}

	void IMapEnts::dump_entityStrings(const std::string& name, char* entityString, int numEntityChars)
	{
		const auto path = name + ".ents"s;
		auto file = filesystem::file(path);
		file.open("wb");
		if (file.get_fp())
		{
			file.write(entityString, numEntityChars, 1);
			file.close();
		}
	}

	void IMapEnts::dump(MapEnts* asset)
	{
		dump_entityStrings(asset->name, asset->entityString, asset->numEntityChars);
		dump_triggers(asset->name, &asset->trigger);
		dump_clientTriggers(asset->name, &asset->clientTrigger);
		dump_clientBlendTriggers(asset->name, &asset->clientTriggerBlend);
		dump_spawnList(asset->name, &asset->spawnList);
		dump_splineList(asset->name, &asset->splineList);
	}
}