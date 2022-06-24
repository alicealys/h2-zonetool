#include <std_include.hpp>
#include "loadedsound.hpp"

#define SIZEOF_SNDFILE_WAVE_HEADER 46

namespace zonetool
{
	LoadedSound* ILoadedSound::parse_flac(const std::string& name, ZoneMemory* mem)
	{
		ZONETOOL_INFO("Parsing loaded_sound \"%s\"...", name.data());

		const auto path = "loaded_sound\\"s + name + ".flac";
		filesystem::file file(path);
		file.open("rb");

		auto* result = mem->Alloc<LoadedSound>();
		result->name = mem->StrDup(name);
		result->info.loadedSize = static_cast<int>(file.size());
		result->info.data = mem->Alloc<char>(result->info.loadedSize);
		file.read(result->info.data, result->info.loadedSize, 1);
		file.close();

		return result;
	}

	LoadedSound* ILoadedSound::parse_wav(const std::string& name, ZoneMemory* mem)
	{
		ZONETOOL_INFO("Parsing loaded_sound \"%s\"...", name.data());

		const auto path = "loaded_sound\\"s + name + ".wav";
		filesystem::file file(path);
		file.open("rb");

		auto* fp = file.get_fp();
		auto* result = mem->Alloc<LoadedSound>();

		unsigned int chunkIDBuffer;
		unsigned int chunkSize;

		fread(&chunkIDBuffer, 4, 1, fp);
		if (chunkIDBuffer != 0x46464952) // RIFF
		{
			ZONETOOL_FATAL("%s: Invalid RIFF Header.", name.data());
		}

		fread(&chunkSize, 4, 1, fp);
		fread(&chunkIDBuffer, 4, 1, fp);

		if (chunkIDBuffer != 0x45564157) // WAVE
		{
			ZONETOOL_FATAL("%s: Invalid WAVE Header.", name.data());
		}

		while (!result->info.data && !feof(fp))
		{
			fread(&chunkIDBuffer, 4, 1, fp);
			fread(&chunkSize, 4, 1, fp);
			switch (chunkIDBuffer)
			{
			case 0x20746D66: // fmt
				if (chunkSize >= 16)
				{
					short format;
					fread(&format, 2, 1, fp);
					if (format != 1 && format != 17)
					{
						ZONETOOL_FATAL("%s: Invalid wave format %i.", name.data(), format);
					}
					result->info.format = format;

					short numChannels;
					fread(&numChannels, 2, 1, fp);
					result->info.channels = static_cast<char>(numChannels);

					int sampleRate;
					fread(&sampleRate, 4, 1, fp);
					result->info.sampleRate = sampleRate;

					int byteRate;
					fread(&byteRate, 4, 1, fp);

					short blockAlign;
					fread(&blockAlign, 2, 1, fp);
					result->info.blockAlign = static_cast<char>(blockAlign);

					short bitPerSample;
					fread(&bitPerSample, 2, 1, fp);
					result->info.numBits = static_cast<char>(bitPerSample);

					if (chunkSize > 16)
					{
						fseek(fp, chunkSize - 16, SEEK_CUR);
					}
				}
				break;

			case 0x61746164: // data
				result->info.data = mem->Alloc<char>(chunkSize);
				fread(result->info.data, 1, chunkSize, fp);

				result->info.loadedSize = chunkSize;
				result->info.dataByteCount = result->info.loadedSize;

				result->info.numSamples = result->info.dataByteCount / (result->info.channels * result->info.numBits / 8);
				break;

			default:
				if (chunkSize > 0)
				{
					fseek(fp, chunkSize, SEEK_CUR);
				}
				break;
			}
		}

		if (!result->info.data)
		{
			ZONETOOL_FATAL("%s: Could not read sounddata.", name.data());
		}

		result->name = mem->StrDup(name);

		file.close();
		return result;
	}

	LoadedSound* ILoadedSound::parse(const std::string& name, ZoneMemory* mem)
	{
		auto path = "loaded_sound\\"s + name;
		if (filesystem::file(path + ".wav").exists())
		{
			return parse_wav(name, mem);
		}
		else if (filesystem::file(path + ".flac").exists())
		{
			return parse_flac(name, mem);
		}

		return nullptr;
	}

	void ILoadedSound::init(const std::string& name, ZoneMemory* mem)
	{
		this->name_ = name;
		this->asset_ = parse(name, mem);

		if (!this->asset_)
		{
			this->asset_ = DB_FindXAssetHeader_Safe(XAssetType(this->type()), this->name_.data()).loadSnd;
		}
	}

	void ILoadedSound::prepare(ZoneBuffer* buf, ZoneMemory* mem)
	{
	}

	void ILoadedSound::load_depending(IZone* zone)
	{
	}

	std::string ILoadedSound::name()
	{
		return this->name_;
	}

	std::int32_t ILoadedSound::type()
	{
		return ASSET_TYPE_LOADED_SOUND;
	}

	void ILoadedSound::write(IZone* zone, ZoneBuffer* buf)
	{
		auto* data = this->asset_;
		auto* dest = buf->write<LoadedSound>(data);

		buf->push_stream(3);

		dest->name = buf->write_str(this->name());

		if (!data->filename.fileIndex)
		{
			if (data->filename.info.raw.dir)
			{
				dest->filename.info.raw.dir = buf->write_str(data->filename.info.raw.dir);
			}
			if (data->filename.info.raw.name)
			{
				dest->filename.info.raw.name = buf->write_str(data->filename.info.raw.name);
			}
		}

		if (data->info.data)
		{
			buf->align(0);
			buf->write(data->info.data, data->info.loadedSize);
			ZoneBuffer::clear_pointer(&dest->info.data);
		}

		buf->pop_stream();
	}

	void ILoadedSound::dump_data(LoadedSound* asset, char* data, size_t size, const std::string& extension)
	{
		const auto path = "loaded_sound\\"s + asset->name + extension;
		auto file = filesystem::file(path);
		file.open("wb");

		file.write(data, size, 1);

		file.close();
	}

	void ILoadedSound::dump(LoadedSound* asset)
	{
		// H1 loaded sound is a hybrid between loaded and streamed sound.
		if (asset)
		{
			// dump data from soundfile
			if (asset->filename.fileIndex)
			{
				auto soundfile_path = utils::string::va("soundfile%d.pak", asset->filename.fileIndex);
				auto soundfile = filesystem::file(soundfile_path);
				soundfile.open("rb", false, true);

				auto* fp = soundfile.get_fp();
				if (fp)
				{
					// get data from sound pak

					bool flac_data = true;

					size_t snd_data_offset = asset->filename.info.packed.offset;
					size_t snd_data_size = asset->filename.info.packed.length;

					std::vector<std::uint8_t> snd_data;
					snd_data.resize(snd_data_size);

					// get data from offset
					fseek(fp, static_cast<long>(snd_data_offset), SEEK_SET);
					fread(snd_data.data(), snd_data_size, 1, fp);

					// check if data is in fLaC format, otherwise it's in WAVE format
					if (!strncmp(reinterpret_cast<char*>(snd_data.data()), "fLaC", 4))
					{
						flac_data = true;
					}
					else
					{
						flac_data = false;

						// get riff header data too
						snd_data_offset -= SIZEOF_SNDFILE_WAVE_HEADER;
						snd_data_size += SIZEOF_SNDFILE_WAVE_HEADER;

						snd_data.resize(snd_data_size);

						// get data from offset
						fseek(fp, static_cast<long>(snd_data_offset), SEEK_SET);
						fread(snd_data.data(), snd_data_size, 1, fp);

						if (strncmp(reinterpret_cast<char*>(snd_data.data()), "RIFF", 4))
						{
							ZONETOOL_FATAL("%s: failed to get wave header from soundfile: %s, offset: %llu",
								asset->name, soundfile_path, asset->filename.info.packed.offset);
						}
					}

					// save data
					dump_data(asset, reinterpret_cast<char*>(snd_data.data()), snd_data_size, flac_data ? ".flac" : ".wav");
				}
				else
				{
					ZONETOOL_FATAL("%s: failed to open soundfile: %s", asset->name, soundfile_path);
				}
			}
			else
			{
				if (asset->info.loadedSize > 4)
				{
					if (!strncmp(asset->info.data, "fLaC", 4))
					{
						// dump flac data from zone
						dump_data(asset, asset->info.data, asset->info.loadedSize, ".flac");
					}
					else
					{
						// dump wav data from zone
						auto file = filesystem::file(utils::string::va("loaded_sound\\%s.wav", asset->name));

						file.open("wb");

						char chunkID[] = { 'R', 'I', 'F', 'F' };
						file.write(chunkID, 4, 1);

						// ChunkSize
						int subchunk1Size = 16;
						int subchunk2Size = asset->info.loadedSize;
						int chunkSize = 4 + (8 + subchunk1Size) + (8 + subchunk2Size);
						file.write(&chunkSize, 4, 1);

						// Format
						char format[] = { 'W', 'A', 'V', 'E' };
						file.write(format, 4, 1);

						// --- FMT SUBCHUNK
						// Subchunk1ID
						char subchunk1ID[] = { 'f', 'm', 't', ' ' };
						file.write(subchunk1ID, 4, 1);

						// Subchunk1Size
						file.write(&subchunk1Size, 4, 1);

						// AudioFormat
						short audioFormat = asset->info.format;
						file.write(&audioFormat, 2, 1);

						// NumChannels
						short numChannels = asset->info.channels;
						file.write(&numChannels, 2, 1);

						// SampleRate
						int sampleRate = asset->info.sampleRate;
						file.write(&sampleRate, 4, 1);

						// ByteRate
						int byteRate = asset->info.sampleRate * asset->info.channels * asset->info.numBits / 8;
						file.write(&byteRate, 4, 1);

						// BlockAlign
						short blockAlign = asset->info.blockAlign;
						file.write(&blockAlign, 2, 1);

						// BitsPerSample
						short bitsPerSample = asset->info.numBits;
						file.write(&bitsPerSample, 2, 1);

						// --- DATA SUBCHUNK
							// Subchunk2ID
						char subchunk2ID[] = { 'd', 'a', 't', 'a' };
						file.write(subchunk2ID, 4, 1);

						// Subchunk2Size
						file.write(&subchunk2Size, 4, 1);

						// Data
						file.write(asset->info.data, asset->info.dataByteCount, 1);

						file.close();
					}
				}
				else
				{
					// null
					dump_data(asset, nullptr, 0);
				}
			}
		}
	}
}