#include <std_include.hpp>
#include "rawfile.hpp"

#include <zlib.h>

namespace zonetool
{
	void IRawFile::dump(RawFile* asset)
	{
		auto f = filesystem::file(asset->name);
		f.open("wb");

		if (asset->compressedLen > 0)
		{
			std::vector<std::uint8_t> uncompressed;
			uncompressed.resize(asset->len);

			uncompress(uncompressed.data(), (uLongf*)&asset->len, (Bytef*)asset->buffer, asset->compressedLen);

			f.write(uncompressed.data(), uncompressed.size(), 1);
		}
		else if (asset->len > 0)
		{
			f.write(asset->buffer, asset->len, 1);
		}

		f.close();
	}
}