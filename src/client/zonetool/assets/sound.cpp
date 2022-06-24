#include <std_include.hpp>
#include "sound.hpp"

namespace zonetool
{
#define SOUND_DUMP_STRING(entry) \
	if (asset->entry) sound[#entry] = std::string(asset->entry); \
	else sound[#entry] = nullptr;
#define SOUND_DUMP_CHAR(entry) \
	sound[#entry] = (char)asset->entry;
#define SOUND_DUMP_INT(entry) \
	sound[#entry] = (int)asset->entry;
#define SOUND_DUMP_FLOAT(entry) \
	sound[#entry] = (float)asset->entry;

#define SOUND_STRING(entry) \
	if (!snddata[#entry].is_null()) { \
		asset->entry = mem->StrDup(snddata[#entry].get<std::string>().data()); \
	} else { asset->entry = nullptr; }
#define SOUND_CHAR(entry) \
	asset->entry = snddata[#entry].get<char>()
#define SOUND_INT(entry) \
	asset->entry = snddata[#entry].get<int>()
#define SOUND_FLOAT(entry) \
	asset->entry = snddata[#entry].get<float>()

	void ISound::json_parse_snd_alias(snd_alias_t* asset, nlohmann::json snddata, ZoneMemory* mem)
	{
		SOUND_STRING(aliasName);
		SOUND_STRING(secondaryAliasName);
		SOUND_STRING(chainAliasName);
		SOUND_STRING(subtitle);
		SOUND_STRING(mixerGroup);

		asset->soundFile = mem->Alloc<SoundFile>();
		asset->soundFile->type = snddata["soundfile"]["type"].get<snd_alias_type_t>();
		asset->soundFile->exists = true;

		if (asset->soundFile->type == SAT_LOADED)
		{
			asset->soundFile->u.loadSnd = mem->Alloc<LoadedSound>();
			asset->soundFile->u.loadSnd->name = mem->StrDup(snddata["soundfile"]["name"].get<std::string>().data());
		}
		else if (asset->soundFile->type == SAT_STREAMED)
		{
			asset->soundFile->u.streamSnd.totalMsec = snddata["soundfile"]["totalMsec"].get<unsigned int>();
			asset->soundFile->u.streamSnd.filename.isLocalized = snddata["soundfile"]["isLocalized"].get<bool>();
			asset->soundFile->u.streamSnd.filename.isStreamed = snddata["soundfile"]["isStreamed"].get<bool>();
			asset->soundFile->u.streamSnd.filename.fileIndex = snddata["soundfile"]["fileIndex"].get<unsigned short>();
			if (asset->soundFile->u.streamSnd.filename.fileIndex)
			{
				asset->soundFile->u.streamSnd.filename.info.packed.offset = snddata["soundfile"]["packed"]["offset"].get<unsigned long long>();
				asset->soundFile->u.streamSnd.filename.info.packed.length = snddata["soundfile"]["packed"]["length"].get<unsigned long long>();
			}
			else
			{
				asset->soundFile->u.streamSnd.filename.info.raw.dir = mem->StrDup(snddata["soundfile"]["raw"]["dir"].get<std::string>().data());
				asset->soundFile->u.streamSnd.filename.info.raw.name = mem->StrDup(snddata["soundfile"]["raw"]["name"].get<std::string>().data());
			}
		}
		else if (asset->soundFile->type == SAT_PRIMED)
		{
			ZONETOOL_FATAL("SAT_PRIMED parsing is not supported yet.");
		}

		SOUND_INT(flags);
		SOUND_INT(sequence);
		SOUND_FLOAT(volMin);
		SOUND_FLOAT(volMax);
		SOUND_INT(volModIndex);
		SOUND_FLOAT(pitchMin);
		SOUND_FLOAT(pitchMax);
		SOUND_FLOAT(distMin);
		SOUND_FLOAT(distMax);
		SOUND_FLOAT(velocityMin);
		SOUND_CHAR(masterPriority);
		SOUND_FLOAT(masterPercentage);
		SOUND_FLOAT(slavePercentage);
		SOUND_FLOAT(probability);
		SOUND_INT(startDelay);

		if (!snddata["sndContext"].is_null())
		{
			asset->sndContext = mem->Alloc<SndContext>();
			asset->sndContext->name = mem->StrDup(snddata["sndContext"].get<std::string>().data());
		}

		if (!snddata["sndCurve"].is_null())
		{
			asset->sndCurve = mem->Alloc<SndCurve>();
			asset->sndCurve->name = mem->StrDup(snddata["sndCurve"].get<std::string>().data());
		}

		if (!snddata["lpfCurve"].is_null())
		{
			asset->lpfCurve = mem->Alloc<SndCurve>();
			asset->lpfCurve->name = mem->StrDup(snddata["lpfCurve"].get<std::string>().data());
		}

		if (!snddata["reverbSendCurve"].is_null())
		{
			asset->reverbSendCurve = mem->Alloc<SndCurve>();
			asset->reverbSendCurve->name = mem->StrDup(snddata["reverbSendCurve"].get<std::string>().data());
		}

		if (!snddata["speakerMap"].is_null())
		{
			asset->speakerMap = mem->Alloc<SpeakerMap>();
			json speakerMap = snddata["speakerMap"];

			asset->speakerMap->name = mem->StrDup(speakerMap["name"].get<std::string>().data());
			asset->speakerMap->isDefault = speakerMap["isDefault"].get<bool>();

			if (!speakerMap["channelMaps"].is_null())
			{
				json channelMaps = speakerMap["channelMaps"];
				for (char x = 0; x < 2; x++)
				{
					for (char y = 0; y < 2; y++)
					{
						if (!channelMaps[(x & 0x01) << 1 | y & 0x01].is_null())
						{
							json channelMap = channelMaps[(x & 0x01) << 1 | y & 0x01];
							asset->speakerMap->channelMaps[x][y].speakerCount = channelMap["speakerCount"].get<int>();

							if (!channelMap["speakers"].is_null())
							{
								json speakers = channelMap["speakers"];

								for (int speaker = 0; speaker < asset->speakerMap->channelMaps[x][y].speakerCount;
									speaker++)
								{
									if (!speakers[speaker].is_null())
									{
										json jspeaker = speakers[speaker];
										asset->speakerMap->channelMaps[x][y].speakers[speaker].speaker =
											jspeaker["speaker"].get<char>();
										asset->speakerMap->channelMaps[x][y].speakers[speaker].numLevels =
											jspeaker["numLevels"].get<char>();
										asset->speakerMap->channelMaps[x][y].speakers[speaker].levels[0] =
											jspeaker["levels0"].get<float>();
										asset->speakerMap->channelMaps[x][y].speakers[speaker].levels[1] =
											jspeaker["levels1"].get<float>();
									}
								}
							}
						}
					}
				}
			}
		}

		SOUND_CHAR(allowDoppler);
		if (!snddata["dopplerPreset"].is_null())
		{
			asset->dopplerPreset = mem->Alloc<DopplerPreset>();
			asset->dopplerPreset->name = mem->StrDup(snddata["dopplerPreset"].get<std::string>().data());
		}

		// parse all unknown things too
		json snd_unknown = snddata["unknown"];
		if (!snd_unknown.is_null())
		{
			auto pad0 = nlohmann::get_object_bytes(snd_unknown["pad"][0]);
			auto pad1 = nlohmann::get_object_bytes(snd_unknown["pad"][1]);
			auto pad2 = nlohmann::get_object_bytes(snd_unknown["pad"][2]);
			auto pad3 = nlohmann::get_object_bytes(snd_unknown["pad"][3]);
			auto pad4 = nlohmann::get_object_bytes(snd_unknown["pad"][4]);
			memcpy(asset->__pad0, pad0.data(), pad0.size());
			memcpy(asset->__pad1, pad1.data(), pad1.size());
			memcpy(asset->__pad2, pad2.data(), pad2.size());
			memcpy(asset->__pad3, pad3.data(), pad3.size());
			memcpy(asset->__pad4, pad4.data(), pad4.size());
			asset->u4 = snd_unknown["u4"].get<int>();
			asset->u5 = snd_unknown["u5"].get<int>();
			asset->u18 = snd_unknown["u18"].get<char>();
			asset->u20 = snd_unknown["u20"].get<char>();
		}
	}

	snd_alias_list_t* ISound::json_parse(const std::string& name, ZoneMemory* mem)
	{
		const auto path = "sounds\\"s + name;
		auto file = filesystem::file(path);
		file.open("rb");

		if (file.get_fp())
		{
			ZONETOOL_INFO("Parsing sound \"%s\"...", name.data());

			auto size = file.size();
			auto bytes = file.read_bytes(size);
			file.close();

			json snddata = json::parse(bytes);

			snd_alias_list_t* asset = mem->Alloc<snd_alias_list_t>();

			SOUND_STRING(aliasName);
			SOUND_CHAR(count);

			asset->head = mem->Alloc<snd_alias_t>(asset->count);

			json heads = snddata["head"];
			for (unsigned char i = 0; i < asset->count; i++)
			{
				json_parse_snd_alias(&asset->head[i], heads[i], mem);
			}

			auto unk = snddata["unknownArray"];
			if (unk.is_array())
			{
				asset->unkCount = static_cast<unsigned char>(unk.size());
				asset->unk = mem->Alloc<short>(asset->unkCount);

				for (unsigned char i = 0; i < asset->unkCount; i++)
				{
					asset->unk[i] = unk[i].get<short>();
				}
			}

			return asset;
		}

		return nullptr;
	}

	snd_alias_list_t* ISound::parse(const std::string& name, ZoneMemory* mem)
	{
		return json_parse(name, mem);
	}

	void ISound::init(const std::string& name, ZoneMemory* mem)
	{
		this->name_ = name;
		this->asset_ = this->parse(name, mem);

		if (!this->asset_)
		{
			this->asset_ = DB_FindXAssetHeader_Safe(XAssetType(this->type()), this->name().data()).sound;
		}
	}

	void ISound::prepare(ZoneBuffer* buf, ZoneMemory* mem)
	{
	}

	void ISound::load_depending(IZone* zone)
	{
		auto* data = this->asset_;

		for (unsigned char i = 0; i < data->count; i++)
		{
			auto* head = &data->head[i];

			if (head->sndContext)
			{
				zone->add_asset_of_type(ASSET_TYPE_SOUND_CONTEXT, head->sndContext->name);
			}

			if (head->sndCurve)
			{
				zone->add_asset_of_type(ASSET_TYPE_SOUND_CURVE, head->sndCurve->name);
			}

			if (head->lpfCurve)
			{
				zone->add_asset_of_type(ASSET_TYPE_LPF_CURVE, head->lpfCurve->name);
			}

			if (head->reverbSendCurve)
			{
				zone->add_asset_of_type(ASSET_TYPE_REVERB_CURVE, head->reverbSendCurve->name);
			}

			if (head->soundFile)
			{
				if (head->soundFile->type == SAT_LOADED)
				{
					zone->add_asset_of_type(ASSET_TYPE_LOADED_SOUND, head->soundFile->u.loadSnd->name);
				}
			}

			if (head->dopplerPreset)
			{
				zone->add_asset_of_type(ASSET_TYPE_DOPPLER_PRESET, head->dopplerPreset->name);
			}
		}
	}

	std::string ISound::name()
	{
		return this->name_;
	}

	std::int32_t ISound::type()
	{
		return ASSET_TYPE_SOUND;
	}

	void ISound::write_soundfile(IZone* zone, ZoneBuffer* buf, SoundFile* data)
	{
		auto* dest = buf->write(data);

		if (data->type == SAT_LOADED)
		{
			if (data->u.loadSnd)
			{
				dest->u.loadSnd = static_cast<LoadedSound*>(zone->get_asset_pointer(
					ASSET_TYPE_LOADED_SOUND, data->u.loadSnd->name));
			}
		}
		else if (data->type == SAT_STREAMED)
		{
			if (!data->u.streamSnd.filename.fileIndex)
			{
				if (data->u.streamSnd.filename.info.raw.dir)
				{
					dest->u.streamSnd.filename.info.raw.dir = buf->write_str(data->u.streamSnd.filename.info.raw.dir);
				}

				if (data->u.streamSnd.filename.info.raw.name)
				{
					dest->u.streamSnd.filename.info.raw.name = buf->write_str(data->u.streamSnd.filename.info.raw.name);
				}
			}
		}
		else if (data->type == SAT_PRIMED)
		{
			if (data->u.loadSnd)
			{
				dest->u.loadSnd = static_cast<LoadedSound*>(zone->get_asset_pointer(
					ASSET_TYPE_LOADED_SOUND, data->u.loadSnd->name));
			}

			if (!data->u.streamSnd.filename.fileIndex)
			{
				if (data->u.streamSnd.filename.info.raw.dir)
				{
					dest->u.streamSnd.filename.info.raw.dir = buf->write_str(data->u.streamSnd.filename.info.raw.dir);
				}

				if (data->u.streamSnd.filename.info.raw.name)
				{
					dest->u.streamSnd.filename.info.raw.name = buf->write_str(data->u.streamSnd.filename.info.raw.name);
				}
			}
		}
	}

	void ISound::write_head(IZone* zone, ZoneBuffer* buf, snd_alias_t* dest)
	{
		auto* data = dest;

		if (data->aliasName)
		{
			dest->aliasName = buf->write_str(data->aliasName);
		}

		if (data->subtitle)
		{
			dest->subtitle = buf->write_str(data->subtitle);
		}

		if (data->secondaryAliasName)
		{
			dest->secondaryAliasName = buf->write_str(data->secondaryAliasName);
		}

		if (data->chainAliasName)
		{
			dest->chainAliasName = buf->write_str(data->chainAliasName);
		}

		if (data->mixerGroup)
		{
			dest->mixerGroup = buf->write_str(data->mixerGroup);
		}

		if (data->soundFile)
		{
			buf->align(3);
			write_soundfile(zone, buf, data->soundFile);
			ZoneBuffer::clear_pointer(&dest->soundFile);
		}

		if (data->sndContext)
		{
			dest->sndContext = static_cast<SndContext*>(zone->get_asset_pointer(
				ASSET_TYPE_SOUND_CONTEXT, data->sndContext->name));
		}

		if (data->sndCurve)
		{
			dest->sndCurve = static_cast<SndCurve*>(zone->get_asset_pointer(
				ASSET_TYPE_SOUND_CURVE, data->sndCurve->name));
		}

		if (data->lpfCurve)
		{
			dest->lpfCurve = static_cast<SndCurve*>(zone->get_asset_pointer(
				ASSET_TYPE_LPF_CURVE, data->lpfCurve->name));
		}

		if (data->reverbSendCurve)
		{
			dest->reverbSendCurve = static_cast<SndCurve*>(zone->get_asset_pointer(
				ASSET_TYPE_REVERB_CURVE, data->reverbSendCurve->name));
		}

		if (data->speakerMap)
		{
			buf->align(3);
			auto* speaker_map = buf->write(data->speakerMap);

			if (speaker_map->name)
			{
				speaker_map->name = buf->write_str(speaker_map->name);
			}

			ZoneBuffer::clear_pointer(&dest->speakerMap);
		}

		if (data->dopplerPreset)
		{
			dest->dopplerPreset = static_cast<DopplerPreset*>(zone->get_asset_pointer(
				ASSET_TYPE_DOPPLER_PRESET, data->dopplerPreset->name));
		}
	}

	void ISound::write(IZone* zone, ZoneBuffer* buf)
	{
		auto* data = this->asset_;
		auto* dest = buf->write(data);

		buf->push_stream(3);

		dest->name = buf->write_str(this->name());

		if (data->head)
		{
			buf->align(3);
			auto* dest_sound = buf->write(data->head, data->count);

			for (unsigned char i = 0; i < data->count; i++)
			{
				write_head(zone, buf, &dest_sound[i]);
			}

			ZoneBuffer::clear_pointer(&dest->head);
		}

		if (data->unk)
		{
			buf->align(1);
			buf->write(data->unk, data->unkCount);
			ZoneBuffer::clear_pointer(&dest->unk);
		}

		buf->pop_stream();
	}

	void ISound::json_dump_snd_alias(ordered_json& sound, snd_alias_t* asset)
	{
		SOUND_DUMP_STRING(aliasName);
		SOUND_DUMP_STRING(secondaryAliasName);
		SOUND_DUMP_STRING(chainAliasName);
		SOUND_DUMP_STRING(subtitle);
		SOUND_DUMP_STRING(mixerGroup);

		// soundfile shit
		if (asset->soundFile)
		{
			sound["soundfile"]["type"] = asset->soundFile->type;

			if (asset->soundFile->exists)
			{
				if (asset->soundFile->type == SAT_LOADED)
				{
					sound["soundfile"]["name"] = asset->soundFile->u.loadSnd->name;
				}
				else if (asset->soundFile->type == SAT_STREAMED)
				{
					sound["soundfile"]["totalMsec"] = asset->soundFile->u.streamSnd.totalMsec;
					sound["soundfile"]["isLocalized"] = asset->soundFile->u.streamSnd.filename.isLocalized;
					sound["soundfile"]["isStreamed"] = asset->soundFile->u.streamSnd.filename.isStreamed;
					sound["soundfile"]["fileIndex"] = asset->soundFile->u.streamSnd.filename.fileIndex;

					sound["soundfile"]["packed"]["offset"] = 0;
					sound["soundfile"]["packed"]["length"] = 0;
					sound["soundfile"]["raw"]["dir"] = "";
					sound["soundfile"]["raw"]["name"] = "";

					if (asset->soundFile->u.streamSnd.filename.fileIndex)
					{
						sound["soundfile"]["packed"]["offset"] = asset->soundFile->u.streamSnd.filename.info.packed.offset;
						sound["soundfile"]["packed"]["length"] = asset->soundFile->u.streamSnd.filename.info.packed.length;
					}
					else
					{
						sound["soundfile"]["raw"]["dir"] = asset->soundFile->u.streamSnd.filename.info.raw.dir
							? asset->soundFile->u.streamSnd.filename.info.raw.dir
							: "";
						sound["soundfile"]["raw"]["name"] = asset->soundFile->u.streamSnd.filename.info.raw.name
							? asset->soundFile->u.streamSnd.filename.info.raw.name
							: "";
					}
				}
				else if (asset->soundFile->type == SAT_PRIMED)
				{
					ZONETOOL_FATAL("SAT_PRIMED dumping is not supported yet.");
				}
			}
		}

		SOUND_DUMP_INT(flags);
		SOUND_DUMP_INT(sequence);
		SOUND_DUMP_FLOAT(volMin);
		SOUND_DUMP_FLOAT(volMax);
		SOUND_DUMP_INT(volModIndex);
		SOUND_DUMP_FLOAT(pitchMin);
		SOUND_DUMP_FLOAT(pitchMax);
		SOUND_DUMP_FLOAT(distMin);
		SOUND_DUMP_FLOAT(distMax);
		SOUND_DUMP_FLOAT(velocityMin);
		SOUND_DUMP_CHAR(masterPriority);
		SOUND_DUMP_FLOAT(masterPercentage);
		SOUND_DUMP_FLOAT(slavePercentage);
		SOUND_DUMP_FLOAT(probability);
		SOUND_DUMP_INT(startDelay);

		if (asset->sndContext)
		{
			sound["sndContext"] = asset->sndContext->name;
		}
		else
		{
			sound["sndContext"] = nullptr;
		}

		if (asset->sndCurve)
		{
			sound["sndCurve"] = asset->sndCurve->name;
		}
		else
		{
			sound["sndCurve"] = nullptr;
		}

		if (asset->lpfCurve)
		{
			sound["lpfCurve"] = asset->lpfCurve->name;
		}
		else
		{
			sound["lpfCurve"] = nullptr;
		}

		if (asset->reverbSendCurve)
		{
			sound["reverbSendCurve"] = asset->reverbSendCurve->name;
		}
		else
		{
			sound["reverbSendCurve"] = nullptr;
		}

		sound["speakerMap"] = nullptr;
		if (asset->speakerMap)
		{
			json speakerMap;
			speakerMap["name"] = asset->speakerMap->name;
			speakerMap["isDefault"] = asset->speakerMap->isDefault;

			json channelMaps;
			for (char x = 0; x < 2; x++)
			{
				for (char y = 0; y < 2; y++)
				{
					json channelMap;
					channelMap["speakerCount"] = asset->speakerMap->channelMaps[x][y].speakerCount;

					json speakers;
					for (int speaker = 0; speaker < asset->speakerMap->channelMaps[x][y].speakerCount; speaker++)
					{
						json jspeaker;

						jspeaker["speaker"] = asset->speakerMap->channelMaps[x][y].speakers[speaker].speaker;
						jspeaker["numLevels"] = asset->speakerMap->channelMaps[x][y].speakers[speaker].numLevels;
						jspeaker["levels0"] = asset->speakerMap->channelMaps[x][y].speakers[speaker].levels[0];
						jspeaker["levels1"] = asset->speakerMap->channelMaps[x][y].speakers[speaker].levels[1];

						speakers[speaker] = jspeaker;
					}

					channelMap["speakers"] = speakers;

					channelMaps[(x & 0x01) << 1 | y & 0x01] = channelMap;
				}
			}

			speakerMap["channelMaps"] = channelMaps;

			sound["speakerMap"] = speakerMap;
		}

		SOUND_DUMP_CHAR(allowDoppler);
		if (asset->dopplerPreset)
		{
			sound["dopplerPreset"] = asset->dopplerPreset->name;
		}
		else
		{
			sound["dopplerPreset"] = nullptr;
		}
		

		// dump all unknown things too
		sound["unknown"]["pad"][0] = json::binary(std::vector<std::uint8_t>(asset->__pad0, asset->__pad0 + sizeof(asset->__pad0)));
		sound["unknown"]["pad"][1] = json::binary(std::vector<std::uint8_t>(asset->__pad1, asset->__pad1 + sizeof(asset->__pad1)));
		sound["unknown"]["pad"][2] = json::binary(std::vector<std::uint8_t>(asset->__pad2, asset->__pad2 + sizeof(asset->__pad2)));
		sound["unknown"]["pad"][3] = json::binary(std::vector<std::uint8_t>(asset->__pad3, asset->__pad3 + sizeof(asset->__pad3)));
		sound["unknown"]["pad"][4] = json::binary(std::vector<std::uint8_t>(asset->__pad4, asset->__pad4 + sizeof(asset->__pad4)));
		sound["unknown"]["u4"] = asset->u4;
		sound["unknown"]["u5"] = asset->u5;
		sound["unknown"]["u18"] = asset->u18;
		sound["unknown"]["u20"] = asset->u20;
	}

	void ISound::json_dump(snd_alias_list_t* asset)
	{
		const auto path = "sounds\\"s + asset->name;

		ordered_json sound;
		ordered_json aliases;
		ordered_json unknownArray;

		SOUND_DUMP_STRING(aliasName);
		SOUND_DUMP_CHAR(count);

		for (unsigned char i = 0; i < asset->count; i++)
		{
			ordered_json alias;
			json_dump_snd_alias(alias, &asset->head[i]);
			sound["head"][i] = alias;
		}

		for (unsigned char i = 0; i < asset->unkCount; i++)
		{
			sound["unknownArray"][i] = asset->unk[i];
		}

		std::string assetstr = sound.dump(4);

		auto file = filesystem::file(path);
		file.open();
		file.write(assetstr.data(), assetstr.size(), 1);
		file.close();
	}

	void ISound::dump(snd_alias_list_t* asset)
	{
		json_dump(asset);
	}
}