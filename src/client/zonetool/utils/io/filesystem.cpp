#include "std_include.hpp"
#include "filesystem.hpp"

namespace zonetool
{
	namespace filesystem
	{
		file::file(const std::string& filepath)
		{
			if (filepath.empty())
			{
				return;
			}

			this->filepath = std::filesystem::path(filepath);
			this->parent_path = this->filepath.parent_path().string();
			this->filename = this->filepath.filename().string();
		}

		file::file()
		{
			this->fp = nullptr;
		}

		file::~file()
		{
			this->close();
		}

		FILE* file::get_fp()
		{
			return this->fp;
		}

		bool file::exists()
		{
			this->open("rb");
			if (this->fp)
			{
				this->close();
				return true;
			}
			return false;
		}

		errno_t file::open(std::string mode, bool use_path)
		{
			if (use_path)
			{
				if (mode[0] == 'r')
				{
					auto path = get_file_path(this->filepath.string());
					if (!path.empty())
					{
						return fopen_s(&this->fp, (path + this->filepath.string()).data(), mode.data());
					}
				}
				if (mode[0] == 'w' || mode[0] == 'a')
				{
					auto path = get_dump_path();
					auto dir = path + this->parent_path;
					create_directory(dir);
					return fopen_s(&this->fp, (path.data() + this->filepath.string()).data(), mode.data());
				}
			}
			return fopen_s(&this->fp, this->filepath.string().data(), mode.data());
		}

		size_t file::write_string(const std::string& str)
		{
			if (this->fp)
			{
				return fwrite(str.data(), str.size(), 1, this->fp);
			}
			return 0;
		}

		size_t file::write_string(const char* str)
		{
			return this->write_string(std::string(str));
		}

		template <typename T> size_t file::write(T val, size_t count)
		{
			if (this->fp)
			{
				return fwrite(&val, sizeof(T), count, this->fp);
			}
			return 0;
		}

		size_t file::write(const void* buffer, size_t size, size_t count)
		{
			if (this->fp)
			{
				return fwrite(buffer, size, count, this->fp);
			}
			return 0;
		}

		size_t file::write(const std::string& str)
		{
			return this->write_string(str);
		}

		size_t file::read(void* buffer, size_t size, size_t count)
		{
			if (this->fp)
			{
				return fread(buffer, size, count, this->fp);
			}
			return 0;
		}

		int file::close()
		{
			if (this->fp)
			{
				return fclose(this->fp);
			}
			return -1;
		}

		bool file::create_path()
		{
			return create_directory(this->parent_path);
		}

		std::size_t file::size()
		{
			if (this->fp)
			{
				auto i = ftell(this->fp);
				fseek(this->fp, 0, SEEK_END);

				auto ret = ftell(this->fp);
				fseek(this->fp, i, SEEK_SET);

				return ret;
			}

			return 0;
		}

		std::vector<std::uint8_t> file::read_bytes(std::size_t size)
		{
			if (this->fp && size)
			{
				// alloc vector
				std::vector<std::uint8_t> buffer;
				buffer.resize(size);

				// read data
				fread(&buffer[0], size, 1, this->fp);

				// return data
				return buffer;
			}

			return {};
		}

		void set_fastfile(const std::string& ff)
		{
			fastfile = ff;
		}

		const std::string& get_fastfile()
		{
			return fastfile;
		}

		std::string get_file_path(const std::string& name)
		{
			std::string path = "";

			path = "zonetool\\" + fastfile + "\\" + name;
			if (std::filesystem::exists(path))
			{
				return "zonetool\\" + fastfile + "\\";
			}

			path = "zonetool\\" + name;
			if (std::filesystem::exists(path))
			{
				return "zonetool\\";
			}

			return "";
		}

		std::string get_dump_path()
		{
			auto path = "dump\\" + fastfile + "\\";
			if (!std::filesystem::exists(path))
			{
				create_directory(path);
			}

			return path;
		}

		bool create_directory(const std::string& name)
		{
			return std::filesystem::create_directories(name);
		}
	}
}