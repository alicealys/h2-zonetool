#pragma once

namespace zonetool
{
	namespace filesystem
	{
		static std::string fastfile;

		class file
		{
		public:
			file(const std::string& filepath);
			file();
			~file();
			FILE* get_fp();
			bool exists();
			errno_t open(std::string mode = "wb", bool use_path = true);
			size_t write_string(const std::string& str);
			size_t write_string(const char* str);
			template <typename T> size_t write(T val, size_t count = 1);
			size_t write(const std::string& str);
			size_t write(const void* buffer, size_t size, size_t count);
			size_t read(void* buffer, size_t size, size_t count);
			int close();

			bool create_path();

			std::size_t size();
			std::vector<uint8_t> read_bytes(std::size_t size);
		private:
			FILE* fp = {};

			std::filesystem::path filepath;
			std::string parent_path;
			std::string filename;
		};

		void set_fastfile(const std::string& ff);
		const std::string& get_fastfile();
		std::string get_file_path(const std::string& name);
		std::string get_dump_path();
		bool create_directory(const std::string& name);
	}
}