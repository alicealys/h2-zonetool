#pragma once
#include "filesystem.hpp"
#include "../zone/zonememory.hpp"

namespace zonetool
{
	namespace assetmanager
	{
		struct dump_entry
		{
			std::uintptr_t ptr;
		};

		enum dump_type : std::uint8_t
		{
			DUMP_TYPE_ERROR = 0,
			DUMP_TYPE_CHAR = 1,
			DUMP_TYPE_SHORT = 2,
			DUMP_TYPE_INT = 3,
			DUMP_TYPE_FLOAT = 4,
			DUMP_TYPE_INT64 = 5,
			DUMP_TYPE_STRING = 6,
			DUMP_TYPE_ASSET = 7,
			DUMP_TYPE_ARRAY = 8,
			DUMP_TYPE_OFFSET = 9,
			DUMP_TYPE_RAW = 10,
			DUMP_TYPE_COUNT = 11,
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

			void write_type(dump_type type)
			{
				file.write(&type);
			}

			void write_existing(std::uint8_t existing)
			{
				file.write(&existing);
			}

			void write_char_internal(std::int8_t c)
			{
				write_type(DUMP_TYPE_CHAR);
				file.write(&c);
			}

			void write_short_internal(std::int16_t s)
			{
				write_type(DUMP_TYPE_SHORT);
				file.write(&s);
			}

			void write_int_internal(std::int32_t s)
			{
				write_type(DUMP_TYPE_INT);
				file.write(&s);
			}

			void write_float_internal(float f)
			{
				write_type(DUMP_TYPE_FLOAT);
				file.write(&f);
			}

			void write_int64_internal(std::int64_t i64)
			{
				write_type(DUMP_TYPE_INT64);
				file.write(&i64);
			}

			void write_string_internal(const char* str)
			{
				file.write_string(str);
			}

			template <typename T>
			void write_internal(const T* data, std::size_t size = sizeof(T), std::size_t count = 1)
			{
				file.write(data, size, count);
			}

			template <typename T>
			void write_array_internal(const T* value, std::uint32_t array_size)
			{
				file.write(value, sizeof(T), array_size);
			}

		public:
			dumper(const std::string& name)
			{
				initialize(name);
			}

			dumper()
			{

			}

			~dumper()
			{
				file.close();
				dump_entries.clear();
			}

			void initialize(const std::string& name)
			{
				file = filesystem::file(name);
				file.open("wb");

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
				return is_open();
			}

			auto open(const std::string& name)
			{
				if (!is_open())
				{
					initialize(name);
				}
				return is_open();
			}

			auto close()
			{
				file.close();
			}

			void dump_char(std::int8_t c)
			{
				write_char_internal(c);
			}

			void dump_short(std::int16_t s)
			{
				write_short_internal(s);
			}

			void dump_int(std::int32_t i)
			{
				write_int_internal(i);
			}

			void dump_float(float f)
			{
				write_float_internal(f);
			}

			void dump_int64(std::int64_t i)
			{
				write_int64_internal(i);
			}

			void dump_string(char* str)
			{
				if (str)
				{
					if (is_entry_dumped(reinterpret_cast<std::uintptr_t>(str)))
					{
						write_type(DUMP_TYPE_OFFSET);
						std::uint32_t index = get_entry_dumped_index(reinterpret_cast<std::uintptr_t>(str));
						write_internal(&index);
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
						std::uint32_t index = get_entry_dumped_index(reinterpret_cast<std::uintptr_t>(asset));
						write_internal(&index);
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
				if (data && array_size)
				{
					if (is_entry_dumped(reinterpret_cast<std::uintptr_t>(data)))
					{
						write_type(DUMP_TYPE_OFFSET);
						std::uint32_t index = get_entry_dumped_index(reinterpret_cast<std::uintptr_t>(data));
						write_internal(&index);
						return;
					}

					add_entry_dumped(reinterpret_cast<std::uintptr_t>(data));

					write_type(DUMP_TYPE_ARRAY);
					write_existing(DUMP_EXISTING);

					write_internal(&array_size);
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

			template <typename T>
			void dump_raw(T* data, std::uint32_t size)
			{
				if (data && size)
				{
					if (is_entry_dumped(reinterpret_cast<std::uintptr_t>(data)))
					{
						write_type(DUMP_TYPE_OFFSET);
						std::uint32_t index = get_entry_dumped_index(reinterpret_cast<std::uintptr_t>(data));
						write_internal(&index);
						return;
					}

					add_entry_dumped(reinterpret_cast<std::uintptr_t>(data));

					write_type(DUMP_TYPE_RAW);
					write_existing(DUMP_EXISTING);

					write_internal(&size);
					write_internal(data, size, 1);
				}
				else
				{
					write_type(DUMP_TYPE_RAW);
					write_existing(DUMP_NONEXISTING);
				}
			}
		};

		// zonetool/iw4/addonmapents.cpp
		class native_reader
		{
		public:
			native_reader(char* data, ZoneMemory* mem)
				: data_(data)
				  , memory(mem)
			{
			}

			template <typename T>
			T read()
			{
				const auto value = *reinterpret_cast<T*>(this->data_);
				this->data_ += sizeof(T);
				return value;
			}

			std::uint32_t read_int()
			{
				const auto type = this->read<char>();
				if (type != 0)
				{
					throw std::runtime_error("asset_reader: invalid type for int\n");
				}

				return this->read<int>();
			}

			template <typename T>
			T* read_array()
			{
				const auto type = this->read<char>();
				if (type != 3)
				{
					throw std::runtime_error("asset_reader: invalid type for array\n");
				}

				const auto size = this->read<int>();
				if (size <= 0)
				{
					printf("asset_reader: array size <= 0\n");
					return nullptr;
				}

				const auto array_ = memory->Alloc<T>(size);
				const auto total_size = sizeof(T) * size;
				std::memcpy(array_, this->data_, total_size);
				this->data_ += total_size;

				return array_;
			}

		private:
			char* data_ = nullptr;
			ZoneMemory* memory;
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

			void read_type(dump_type* type)
			{
				file.read(type);
			}

			void read_existing(std::uint8_t* existing)
			{
				file.read(existing);
			}

			void read_char_internal(std::int8_t* c)
			{
				dump_type type = DUMP_TYPE_ERROR;
				read_type(&type);
				if (type != DUMP_TYPE_CHAR)
				{
					printf("Reader error: Type not DUMP_TYPE_CHAR but %i\n", type);
					throw std::runtime_error("Reader error: Type not DUMP_TYPE_CHAR");
				}
				file.read(c);
			}

			void read_short_internal(std::int16_t* s)
			{
				dump_type type = DUMP_TYPE_ERROR;
				read_type(&type);
				if (type != DUMP_TYPE_SHORT)
				{
					printf("Reader error: Type not DUMP_TYPE_SHORT but %i\n", type);
					throw std::runtime_error("Reader error: Type not DUMP_TYPE_SHORT");
				}
				file.read(s);
			}

			void read_int_internal(std::int32_t* i)
			{
				dump_type type = DUMP_TYPE_ERROR;
				read_type(&type);
				if (type != DUMP_TYPE_INT)
				{
					printf("Reader error: Type not DUMP_TYPE_INT but %i\n", type);
					throw std::runtime_error("Reader error: Type not DUMP_TYPE_INT");
				}
				file.read(i);
			}

			void read_float_internal(float* f)
			{
				dump_type type = DUMP_TYPE_ERROR;
				read_type(&type);
				if (type != DUMP_TYPE_FLOAT)
				{
					printf("Reader error: Type not DUMP_TYPE_FLOAT but %i\n", type);
					throw std::runtime_error("Reader error: Type not DUMP_TYPE_FLOAT");
				}
				file.read(f);
			}

			void read_int64_internal(std::int64_t* i)
			{
				dump_type type = DUMP_TYPE_ERROR;
				read_type(&type);
				if (type != DUMP_TYPE_INT64)
				{
					printf("Reader error: Type not DUMP_TYPE_INT64 but %i\n", type);
					throw std::runtime_error("Reader error: Type not DUMP_TYPE_INT64");
				}
				file.read(i);
			}

			void read_string_internal(std::string* str)
			{
				file.read_string(str);
			}

			template <typename T>
			void read_internal(T* value, std::size_t size = sizeof(T), std::size_t count = 1)
			{
				file.read(value, size, count);
			}

			template <typename T>
			void read_array_internal(T* value, std::uint32_t array_size)
			{
				file.read(value, sizeof(T), array_size);
			}

		public:
			reader(const std::string& name, ZoneMemory* mem)
			{
				memory = mem;
				initialize(name);
			}

			reader(ZoneMemory* mem)
			{
				memory = mem;
			}

			~reader()
			{
				file.close();
				read_entries.clear();
			}

			void initialize(const std::string& name)
			{
				file = filesystem::file(name);
				file.open("rb");

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
				return is_open();
			}

			auto open(const std::string& name)
			{
				if (!is_open())
				{
					initialize(name);
				}
				return is_open();
			}

			auto close()
			{
				file.close();
			}

			std::int8_t read_char()
			{
				std::int8_t c;
				read_char_internal(&c);
				return c;
			}

			std::int16_t read_short()
			{
				std::int16_t s;
				read_short_internal(&s);
				return s;
			}

			std::int32_t read_int()
			{
				std::int32_t i;
				read_int_internal(&i);
				return i;
			}

			float dump_float()
			{
				float f;
				read_float_internal(&f);
				return f;
			}

			std::int64_t read_int64()
			{
				std::int64_t i;
				read_int64_internal(&i);
				return i;
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
				else
				{
					printf("Reader error: Type not DUMP_TYPE_STRING or DUMP_TYPE_OFFSET but %i\n", type);
					throw std::runtime_error("Reader error: Type not DUMP_TYPE_STRING or DUMP_TYPE_OFFSET");
				}

				//return nullptr;
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

					T* asset = memory->Alloc<T>();
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
				else
				{
					printf("Reader error: Type not DUMP_TYPE_ASSET or DUMP_TYPE_OFFSET but %i\n", type);
					throw std::runtime_error("Reader error: Type not DUMP_TYPE_ASSET or DUMP_TYPE_OFFSET");
				}

				//return nullptr;
			}

			template <typename T>
			T* read_array()
			{
				dump_type type;
				read_type(&type);

				if (type == DUMP_TYPE_ARRAY)
				{
					std::uint8_t existing;
					read_existing(&existing);

					if (existing == DUMP_NONEXISTING)
					{
						return nullptr;
					}

					std::uint32_t array_size;
					read_internal(&array_size);

					if (!array_size)
					{
						return nullptr;
					}

					T* array_ = memory->Alloc<T>(array_size);
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
				else
				{
					printf("Reader error: Type not DUMP_TYPE_ARRAY or DUMP_TYPE_OFFSET but %i\n", type);
					throw std::runtime_error("Reader error: Type not DUMP_TYPE_ARRAY or DUMP_TYPE_OFFSET");
				}

				//return nullptr;
			}

			template <typename T>
			T* read_single()
			{
				return read_array<T>();
			}

			template <typename T>
			T* read_raw()
			{
				dump_type type;
				read_type(&type);

				if (type == DUMP_TYPE_RAW)
				{
					std::uint8_t existing;
					read_existing(&existing);

					if (existing == DUMP_NONEXISTING)
					{
						return nullptr;
					}

					std::uint32_t size;
					read_internal(&size);

					if (!size)
					{
						return nullptr;
					}

					T* data = memory->Alloc<T>(size);
					read_internal(data, size, 1);

					add_entry_read(reinterpret_cast<std::uintptr_t>(data));

					return data;
				}
				else if (type == DUMP_TYPE_OFFSET)
				{
					std::uint32_t index;
					read_internal(&index);

					std::uintptr_t ptr = get_entry_read_from_index(index);
					return reinterpret_cast<T*>(ptr);
				}
				else
				{
					printf("Reader error: Type not DUMP_TYPE_RAW or DUMP_TYPE_OFFSET but %i\n", type);
					throw std::runtime_error("Reader error: Type not DUMP_TYPE_RAW or DUMP_TYPE_OFFSET");
				}

				//return nullptr;
			}
		};
	}
}