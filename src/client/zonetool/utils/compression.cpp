#include <std_include.hpp>

#include "compression.hpp"

#include <zstd.h>
#include <zlib.h>

#include <lz4.h>
#include <lz4hc.h>
#include <lz4frame.h>

#include <tomcrypt.h>

#define LZ4_COMPRESSION 4
#define MAX_BLOCK_SIZE 0x10000ull

namespace compression
{
	namespace
	{
		size_t align_value(size_t value, unsigned int alignment)
		{
			const auto diff = value % 4;
			return diff != 0
				? value + (4 - diff)
				: value;
		}

		const char* align_value(const char* value, unsigned int alignment)
		{
			return reinterpret_cast<const char*>(
				align_value(reinterpret_cast<size_t>(value), alignment));
		}
	}

	std::vector<std::uint8_t> compress_lz4_block(const void* data, const size_t size)
	{
		std::vector<std::uint8_t> out_buffer;

		auto bytes_to_compress = size;
		if (bytes_to_compress > std::numeric_limits<unsigned int>::max())
		{
			throw std::runtime_error("cannot compress more than `std::numeric_limits<unsigned int>::max()` bytes");
		}

		auto data_ptr = reinterpret_cast<const char*>(data);

		const auto write = [&](void* data, const size_t len)
		{
			for (auto i = 0ull; i < len; i++)
			{
				out_buffer.push_back(reinterpret_cast<char*>(data)[i]);
			}
		};

		auto first_block = true;

		while (bytes_to_compress > 0)
		{
			const auto block_size = static_cast<unsigned int>(std::min(bytes_to_compress, MAX_BLOCK_SIZE));
			const auto bound = LZ4_compressBound(block_size);

			std::string buffer;
			buffer.resize(bound);

			const auto compressed_size = LZ4_compress_fast(data_ptr, 
				buffer.data(), block_size, bound, 1);
			buffer.resize(align_value(compressed_size, 4));

			if (first_block)
			{
				compressed_block_header header{};
				header.unknown2 = 1;
				header.compression_type = LZ4_COMPRESSION;
				header.uncompressed_size = static_cast<unsigned int>(bytes_to_compress);
				header.compressed_size = compressed_size;
				header.uncompressed_block_size = block_size;

				write(&header, sizeof(header));
			}
			else
			{
				intermediate_header header{};
				header.compressed_size = compressed_size;
				header.uncompressed_block_size = block_size;

				write(&header, sizeof(header));
			}

			write(buffer.data(), buffer.size());

			first_block = false;

			bytes_to_compress -= block_size;
			data_ptr += block_size;
		}

		return out_buffer;
	}

	std::vector<std::uint8_t> compress_lz4_block(const std::vector<std::uint8_t>& data, const size_t size)
	{
		return compress_lz4_block(data.data(), size);
	}

	std::vector<std::uint8_t> compress_lz4_block(const std::vector<std::uint8_t>& data)
	{
		return compress_lz4_block(data, data.size());
	}

	std::string compress_lz4_block(const std::string& data)
	{
		const auto compressed = compress_lz4_block(data.data(), data.size());
		return {compressed.begin(), compressed.end()};
	}

	std::vector<std::uint8_t> decompress_lz4_block(const void* data, const size_t size)
	{
		std::vector<std::uint8_t> out_buffer;

		auto data_ptr = reinterpret_cast<const char*>(data);
		auto end_ptr = data_ptr + size;

		const auto write = [&](void* data, const size_t len)
		{
			for (auto i = 0ull; i < len; i++)
			{
				out_buffer.push_back(reinterpret_cast<char*>(data)[i]);
			}
		};

		auto first_block = true;

		compressed_block_header header{};

		while (data_ptr < end_ptr)
		{
			if (first_block)
			{
				header = *reinterpret_cast<compressed_block_header*>(
					reinterpret_cast<size_t>(data_ptr));

				data_ptr += sizeof(compressed_block_header);
			}
			else
			{
				const auto int_header = reinterpret_cast<intermediate_header*>(
					reinterpret_cast<size_t>(data_ptr));

				header.compressed_size = int_header->compressed_size;
				header.uncompressed_size = int_header->uncompressed_block_size;
				header.uncompressed_block_size = int_header->uncompressed_block_size;

				data_ptr += sizeof(intermediate_header);
			}

			if (header.compression_type != 4)
			{
				throw std::runtime_error("invalid compression type");
			}

			std::string buffer;
			buffer.resize(header.uncompressed_block_size);

			const auto read_count = static_cast<unsigned int>(LZ4_decompress_safe(data_ptr, buffer.data(), 
				header.compressed_size, header.uncompressed_block_size));

			if (read_count != header.uncompressed_block_size)
			{
				throw std::runtime_error("bad read");
			}

			first_block = false;

			data_ptr += header.compressed_size;
			data_ptr = align_value(data_ptr, 4);

			write(buffer.data(), buffer.size());
		}

		return out_buffer;
	}

	std::vector<std::uint8_t> decompress_lz4_block(const std::vector<std::uint8_t>& data, const size_t size)
	{
		return decompress_lz4_block(data.data(), size);
	}

	std::vector<std::uint8_t> decompress_lz4_block(const std::vector<std::uint8_t>& data)
	{
		return decompress_lz4_block(data, data.size());
	}

	std::string decompress_lz4_block(const std::string& data)
	{
		const auto decompressed = compress_lz4_block(data.data(), data.size());
		return {decompressed.begin(), decompressed.end()};
	}
}
