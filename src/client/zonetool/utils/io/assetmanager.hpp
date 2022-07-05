#pragma once
#include "filesystem.hpp"
#include "../zone/zonememory.hpp"

#define ASSETMAN_MAGIC "assetman"
#define ASSETMAN_VERSION 1

namespace zonetool
{
	namespace assetmanager
	{
		struct dump_header
		{
			char magic[8];
			std::uint32_t version;
		};

		struct dump_entry
		{
			std::uintptr_t ptr;
		};

		enum dump_type : std::uint8_t
		{
			DUMP_TYPE_STRING = 0,
			DUMP_TYPE_ASSET = 1,
			DUMP_TYPE_ARRAY = 2,
			DUMP_TYPE_OFFSET = 3,
		};

		const std::uint8_t DUMP_EXISTING = 1;
		const std::uint8_t DUMP_NONEXISTING = 0;

		class dumper
		{
		private:
			filesystem::file file;
			std::vector<dump_entry> dump_entries;

			bool is_entry_dumped(std::uintptr_t ptr)
			{
				for (std::size_t i = 0; i < dump_entries.size(); i++)
				{
					if (dump_entries[i].ptr == ptr)
					{
						return true;
					}
				}
				return false;
			}

			std::int32_t get_entry_dumped_index(std::uintptr_t ptr)
			{
				for (std::size_t i = 0; i < dump_entries.size(); i++)
				{
					if (dump_entries[i].ptr == ptr)
					{
						return static_cast<std::int32_t>(i);
					}
				}
				return static_cast<std::int32_t>(-1);
			}

			void add_entry_dumped(std::uintptr_t str)
			{
				dump_entry entry;
				entry.ptr = str;
				dump_entries.push_back(entry);
			}

			void write_header()
			{
				dump_header header;

				memset(header.magic, 0, sizeof(header.magic));
				strcpy(header.magic, ASSETMAN_MAGIC);

				header.version = ASSETMAN_VERSION;

				file.write(&header);
			}

			void write_type(dump_type type)
			{
				file.write(&type);
			}

			void write_existing(std::uint8_t existing)
			{
				file.write(&existing);
			}

			void write_string_internal(const char* str)
			{
				file.write_string(str);
			}

			template <typename T>
			void write_internal(const T& value)
			{
				file.write(&value, sizeof(T), 1);
			}

			void write_array_size_internal(std::uint32_t array_size)
			{
				file.write(&array_size);
			}

			template <typename T>
			void write_array_internal(const T* value, std::uint32_t array_size)
			{
				file.write(value, sizeof(T), array_size);
			}

		public:
			dumper(const std::string& name)
			{
				file = filesystem::file(name);
				file.open("wb");

				dump_entries.clear();

				write_header();
			}

			~dumper()
			{
				file.close();
				dump_entries.clear();
			}

			bool is_open()
			{
				return file.get_fp() != nullptr;
			}

			auto open()
			{
				if (!is_open())
				{
					file.open("wb");
				}
			}

			auto close()
			{
				file.close();
			}

			void dump_string(char* str)
			{
				if (str)
				{
					if (is_entry_dumped(reinterpret_cast<std::uintptr_t>(str)))
					{
						write_type(DUMP_TYPE_OFFSET);
						write_internal(get_entry_dumped_index(reinterpret_cast<std::uintptr_t>(str)));
						return;
					}

					add_entry_dumped(reinterpret_cast<std::uintptr_t>(str));

					write_type(DUMP_TYPE_STRING);
					write_existing(DUMP_EXISTING);

					write_string_internal(str);
				}
				else
				{
					write_type(DUMP_TYPE_STRING);
					write_existing(DUMP_NONEXISTING);
				}
			}

			void dump_string(const char* s)
			{
				dump_string(const_cast<char*>(s));
			}

			template <typename T>
			void dump_asset(T* asset)
			{
				if (asset && asset->name)
				{
					if (is_entry_dumped(reinterpret_cast<std::uintptr_t>(asset)))
					{
						write_type(DUMP_TYPE_OFFSET);
						write_internal(get_entry_dumped_index(reinterpret_cast<std::uintptr_t>(asset)));
						return;
					}

					add_entry_dumped(reinterpret_cast<std::uintptr_t>(asset));

					write_type(DUMP_TYPE_ASSET);
					write_existing(DUMP_EXISTING);

					write_string_internal(asset->name);
				}
				else
				{
					write_type(DUMP_TYPE_ASSET);
					write_existing(DUMP_NONEXISTING);
				}
			}

			template <typename T>
			void dump_array(T* data, std::uint32_t array_size)
			{
				if (data && array_size > 0)
				{
					if (is_entry_dumped(reinterpret_cast<std::uintptr_t>(data)))
					{
						write_type(DUMP_TYPE_OFFSET);
						write_internal(get_entry_dumped_index(reinterpret_cast<std::uintptr_t>(data)));
						return;
					}

					add_entry_dumped(reinterpret_cast<std::uintptr_t>(data));

					write_type(DUMP_TYPE_ARRAY);
					write_existing(DUMP_EXISTING);

					write_array_size_internal(array_size);
					write_array_internal(data, array_size);
				}
				else
				{
					write_type(DUMP_TYPE_ARRAY);
					write_existing(DUMP_NONEXISTING);
				}
			}

			template <typename T>
			void dump_array(const T* data, std::uint32_t array_size)
			{
				dump_array<T>(const_cast<T*>(data), array_size);
			}

			template <typename T>
			void dump_single(T* asset)
			{
				dump_array<T>(asset, 1);
			}
		};

		class reader
		{
		private:
			filesystem::file file;
			std::vector<dump_entry> read_entries;
			ZoneMemory* memory;

			std::uintptr_t get_entry_read_from_index(std::uint32_t index)
			{
				if (index > read_entries.size())
				{
					return reinterpret_cast<std::uintptr_t>(nullptr);
				}
				return read_entries[index].ptr;
			}

			void add_entry_read(std::uintptr_t str)
			{
				dump_entry entry;
				entry.ptr = str;
				read_entries.push_back(entry);
			}

			void check_magic(const char* magic)
			{
				if (strncmp(magic, ASSETMAN_MAGIC, sizeof(ASSETMAN_MAGIC)))
				{
					throw("Magic is wrong!");
				}
			}

			void check_version(std::uint32_t version)
			{
				if (version != ASSETMAN_VERSION)
				{
					throw("Version is wrong!");
				}
			}

			void read_header()
			{
				dump_header header;

				file.read(&header);

				check_magic(header.magic);
				check_version(header.version);
			}

			void read_type(dump_type* type)
			{
				file.read(type);
			}

			void read_existing(std::uint8_t* existing)
			{
				file.read(existing);
			}

			void read_string_internal(std::string* str)
			{
				file.read_string(str);
			}

			template <typename T>
			void read_internal(T* value)
			{
				file.read(value, sizeof(T), 1);
			}

			void read_array_size_internal(std::uint32_t* array_size)
			{
				file.read(array_size);
			}

			template <typename T>
			void read_array_internal(T* value, std::uint32_t array_size)
			{
				file.read(value, sizeof(T), array_size);
			}

		public:
			reader(const std::string& name, ZoneMemory* mem)
			{
				file = filesystem::file(name);
				file.open("rb");

				memory = mem;

				read_entries.clear();

				read_header();
			}

			~reader()
			{
				file.close();
				read_entries.clear();
			}

			bool is_open()
			{
				return file.get_fp() != nullptr;
			}

			auto open()
			{
				if (!is_open())
				{
					file.open("rb");
				}
			}

			auto close()
			{
				file.close();
			}

			char* read_string()
			{
				dump_type type;
				read_type(&type);

				if (type == DUMP_TYPE_STRING)
				{
					std::uint8_t existing;
					read_existing(&existing);

					if (existing == DUMP_NONEXISTING)
					{
						return nullptr;
					}

					std::string str;
					read_string_internal(&str);

					char* ret_str = memory->Alloc<char>(str.size() + 1);
					strcpy(ret_str, str.c_str());

					add_entry_read(reinterpret_cast<std::uintptr_t>(ret_str));

					return ret_str;
				}
				else if (type == DUMP_TYPE_OFFSET)
				{
					std::uint32_t index;
					read_internal(&index);

					std::uintptr_t ptr = get_entry_read_from_index(index);
					return reinterpret_cast<char*>(ptr);
				}

				printf("Reader error: Type not DUMP_TYPE_STRING or DUMP_TYPE_OFFSET but %i", type);
				__debugbreak();

				return nullptr;
			}

			template <typename T>
			T* read_asset()
			{
				dump_type type;
				read_type(&type);

				if (type == DUMP_TYPE_ASSET)
				{
					std::uint8_t existing;
					read_existing(&existing);

					if (existing == DUMP_NONEXISTING)
					{
						return nullptr;
					}

					std::string str;
					read_string_internal(&str);

					char* name = memory->Alloc<char>(str.size() + 1);
					strcpy(name, str.c_str());

					auto asset = memory->Alloc<T>();
					memset(asset, 0, sizeof(T));
					asset->name = const_cast<char*>(name);

					add_entry_read(reinterpret_cast<std::uintptr_t>(asset));

					return asset;
				}
				else if (type == DUMP_TYPE_OFFSET)
				{
					std::uint32_t index;
					read_internal(&index);

					std::uintptr_t ptr = get_entry_read_from_index(index);
					return reinterpret_cast<T*>(ptr);
				}

				printf("Reader error: Type not DUMP_TYPE_ASSET or DUMP_TYPE_OFFSET but %i", type);
				__debugbreak();

				return nullptr;
			}

			template <typename T>
			T* read_array()
			{
				dump_type type;
				read_type(&type);

				if (type == DUMP_TYPE_ARRAY)
				{
					std::uint32_t array_size;
					read_array_size_internal(&array_size);

					if (array_size <= 0)
					{
						return nullptr;
					}

					auto array_ = memory->Alloc<T>(array_size);
					read_array_internal(array_, array_size);

					add_entry_read(reinterpret_cast<std::uintptr_t>(array_));

					return array_;
				}
				else if (type == DUMP_TYPE_OFFSET)
				{
					std::uint32_t index;
					read_internal(&index);

					std::uintptr_t ptr = get_entry_read_from_index(index);
					return reinterpret_cast<T*>(ptr);
				}

				printf("Reader error: Type not DUMP_TYPE_ARRAY or DUMP_TYPE_OFFSET but %i", type);
				__debugbreak();

				return nullptr;
			}

			template <typename T> T* read_single()
			{
				return read_array<T>();
			}
		};
	}
}