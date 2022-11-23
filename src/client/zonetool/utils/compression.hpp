#pragma once

namespace compression
{
	struct compressed_block_header
	{
		int uncompressed_size;
		unsigned char unknown1[6]; // always 0
		unsigned char unknown2; // always 1
		unsigned char compression_type; // LZ4
		unsigned int compressed_size;
		unsigned int uncompressed_block_size;
	};

	struct intermediate_header
	{
		unsigned int compressed_size;
		unsigned int uncompressed_block_size;
	};

	std::vector<std::uint8_t> compress_lz4_block(const void* data, const size_t size);
	std::vector<std::uint8_t> compress_lz4_block(const std::vector<std::uint8_t>& data);
	std::vector<std::uint8_t> compress_lz4_block(const std::vector<std::uint8_t>& data, const size_t size);
	std::string compress_lz4_block(const std::string& data);

	std::vector<std::uint8_t> decompress_lz4_block(const void* data, const size_t size);
	std::vector<std::uint8_t> decompress_lz4_block(const std::vector<std::uint8_t>& data);
	std::vector<std::uint8_t> decompress_lz4_block(const std::vector<std::uint8_t>& data, const size_t size);
	std::string decompress_lz4_block(const std::string& data);
}
