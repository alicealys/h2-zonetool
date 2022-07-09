#include <std_include.hpp>
#include "gfximage.hpp"

#include "zonetool/utils/s3tc.hpp"
#pragma warning( push )
#pragma warning( disable : 4459 )
#include <DirectXTex.h>
#pragma warning( pop )

//#define IMAGE_DECOMPRESS_DXT
//#define IMAGE_DUMP_DDS

namespace zonetool
{
	namespace
	{
		bool is_map_image(const std::string& name)
		{
			return (name.size() >= 6)
				? ((name.substr(0, 6) == "*light" || name.substr(0, 6) == "*refle" ||
					name == "$outdoor")
					? true
					: false)
				: false;
		}

		std::string clean_name(const std::string& name)
		{
			auto new_name = name;

			for (auto i = 0u; i < name.size(); i++)
			{
				switch (new_name[i])
				{
				case '*':
					new_name[i] = '_';
					break;
				}
			}

			return new_name;
		}
	}

	namespace iwi
	{
		namespace shared
		{
			enum GfxImageFileFormat : std::uint8_t
			{
				IMG_FORMAT_INVALID = 0x0,
				IMG_FORMAT_BITMAP_RGBA = 0x1,
				IMG_FORMAT_BITMAP_RGB = 0x2,
				IMG_FORMAT_BITMAP_LUMINANCE_ALPHA = 0x3,
				IMG_FORMAT_BITMAP_LUMINANCE = 0x4,
				IMG_FORMAT_BITMAP_ALPHA = 0x5,
				IMG_FORMAT_WAVELET_RGBA = 0x6,
				IMG_FORMAT_WAVELET_RGB = 0x7,
				IMG_FORMAT_WAVELET_LUMINANCE_ALPHA = 0x8,
				IMG_FORMAT_WAVELET_LUMINANCE = 0x9,
				IMG_FORMAT_WAVELET_ALPHA = 0xA,
				IMG_FORMAT_DXT1 = 0xB,
				IMG_FORMAT_DXT3 = 0xC,
				IMG_FORMAT_DXT5 = 0xD,
				IMG_FORMAT_DXN = 0xE,
				IMG_FORMAT_DXT3A_AS_LUMINANCE = 0xF,
				IMG_FORMAT_DXT5A_AS_LUMINANCE = 0x10,
				IMG_FORMAT_DXT3A_AS_ALPHA = 0x11,
				IMG_FORMAT_DXT5A_AS_ALPHA = 0x12,
				IMG_FORMAT_DXT1_AS_LUMINANCE_ALPHA = 0x13,
				IMG_FORMAT_DXN_AS_LUMINANCE_ALPHA = 0x14,
				IMG_FORMAT_DXT1_AS_LUMINANCE = 0x15,
				IMG_FORMAT_DXT1_AS_ALPHA = 0x16,
				IMG_FORMAT_COUNT = 0x17,
			};
		}
		using namespace shared;

		namespace iw5
		{
			enum IMG_FLAGS : std::uint32_t
			{
				IMG_FLAG_NOPICMIP = 0x1,
				IMG_FLAG_NOMIPMAPS = 0x2,
				IMG_FLAG_STREAMING = 0x4,
				IMG_FLAG_LEGACY_NORMALS = 0x8,
				IMG_FLAG_CLAMP_U = 0x10,
				IMG_FLAG_CLAMP_V = 0x20,
				IMG_FLAG_ALPHA_WEIGHTED_COLORS = 0x40,
				IMG_FLAG_DXTC_APPROX_WEIGHTS = 0x80,
				IMG_FLAG_GAMMA_NONE = 0x0,
				IMG_FLAG_GAMMA_SRGB = 0x100,
				IMG_FLAG_GAMMA_PWL = 0x200,
				IMG_FLAG_GAMMA_2 = 0x300,
				IMG_FLAG_MAPTYPE_2D = 0x0,
				IMG_FLAG_MAPTYPE_CUBE = 0x10000,
				IMG_FLAG_MAPTYPE_3D = 0x20000,
				IMG_FLAG_MAPTYPE_1D = 0x30000,
				IMG_FLAG_NORMALMAP = 0x40000,
				IMG_FLAG_INTENSITY_TO_ALPHA = 0x80000,
				IMG_FLAG_DYNAMIC = 0x1000000,
				IMG_FLAG_RENDER_TARGET = 0x2000000,
				IMG_FLAG_SYSTEMMEM = 0x4000000,
			};

			struct GfxImageFileHeader
			{
				char tag[3];
				char version;
				unsigned int flags;
				GfxImageFileFormat format;
				char unused;
				short dimensions[3];
				int fileSizeForPicmip[4];
			};
		}

		namespace iw3
		{
			enum IMG_FLAGS : std::uint32_t
			{
				IMG_FLAG_NOPICMIP = 0x1,
				IMG_FLAG_NOMIPMAPS = 0x2,
				IMG_FLAG_CUBEMAP = 0x4,
				IMG_FLAG_VOLMAP = 0x8,
				IMG_FLAG_STREAMING = 0x10,
				IMG_FLAG_LEGACY_NORMALS = 0x20,
				IMG_FLAG_CLAMP_U = 0x40,
				IMG_FLAG_CLAMP_V = 0x80,
				IMG_FLAG_DYNAMIC = 0x10000,
				IMG_FLAG_RENDER_TARGET = 0x20000,
				IMG_FLAG_SYSTEMMEM = 0x40000,
			};

			struct GfxImageFileHeader
			{
				char tag[3];
				char version;
				GfxImageFileFormat format;
				unsigned char flags;
				short dimensions[3];
				int fileSizeForPicmip[4];
			};
		}

		GfxImage* parse(const std::string& name, ZoneMemory* mem)
		{
			const auto path = utils::string::va("images\\%s.iwi", clean_name(name).data());
			auto file = filesystem::file(path);
			file.open("rb");
			if (file.get_fp())
			{
				auto size = file.size();
				auto bytes = file.read_bytes(size);
				file.close();

				const auto version = bytes[3];

				if (version == 8 || version == 9) // iw4, iw5
				{
					ZONETOOL_INFO("Parsing IWI image \"%s\", version (%i)", name.data(), version);

					std::vector<std::uint8_t> pixels;
					auto iwi_header = reinterpret_cast<iw5::GfxImageFileHeader*>(bytes.data());

					if (iwi_header->format != IMG_FORMAT_DXT1 &&
						iwi_header->format != IMG_FORMAT_DXT3 &&
						iwi_header->format != IMG_FORMAT_DXT5)
					{
						ZONETOOL_ERROR("IWI format is not DXT1, DXT3 or DXT5 for image \"%s.iwi\"", name.data());
						return nullptr;
					}

					if ((iwi_header->flags & iw5::IMG_FLAGS::IMG_FLAG_MAPTYPE_CUBE) != 0) // parse cube
					{
						if (iwi_header->fileSizeForPicmip[0] > iwi_header->fileSizeForPicmip[1]) // has mipmaps
						{
							ZONETOOL_FATAL("Cube IWI \"%s\" has mipmaps...", name.data());
						}

						std::uint8_t* pixel_data = bytes.data() + sizeof(iw5::GfxImageFileHeader);
						std::size_t pixel_data_size = bytes.size() - sizeof(iw5::GfxImageFileHeader);

						// zone image
						auto* image = mem->Alloc<GfxImage>();
						image->mapType = MAPTYPE_CUBE;
						image->sematic = 2;
						image->category = 3;
						image->flags = 2;
						image->width = iwi_header->dimensions[0];
						image->height = iwi_header->dimensions[1];
						image->depth = iwi_header->dimensions[2];

						const unsigned int data_len = static_cast<unsigned int>(pixel_data_size);

						switch (iwi_header->format)
						{
						case IMG_FORMAT_DXT1:
							image->imageFormat = DXGI_FORMAT_BC1_UNORM;
							break;
						case IMG_FORMAT_DXT3:
							image->imageFormat = DXGI_FORMAT_BC2_UNORM;
							break;
						case IMG_FORMAT_DXT5:
							image->imageFormat = DXGI_FORMAT_BC3_UNORM;
							break;
						}
						image->pixelData = mem->Alloc<unsigned char>(data_len);
						memcpy(image->pixelData, pixel_data, data_len);

						image->dataLen1 = data_len;
						image->dataLen2 = data_len;

						image->numElements = 1;
						image->levelCount = 1;
						image->streamed = false;

						image->name = mem->StrDup(name);

						return image;
					}
					else if ((iwi_header->flags & iw5::IMG_FLAGS::IMG_FLAG_MAPTYPE_3D) != 0) // parse 3d
					{
						ZONETOOL_FATAL("3D IWI files are not supported yet! (%s.iwi)", name.data());
					}
					else if ((iwi_header->flags & iw5::IMG_FLAGS::IMG_FLAG_MAPTYPE_1D) != 0) // parse 1d
					{
						ZONETOOL_FATAL("1D IWI files are not supported yet! (%s.iwi)", name.data());
					}
					else // parse 2d
					{
						std::uint8_t* pixel_data;
						std::size_t pixel_data_size = 0;
						if (iwi_header->fileSizeForPicmip[0] > iwi_header->fileSizeForPicmip[1]) // has mipmaps
						{
							unsigned int compressed_size = 0;
							switch (iwi_header->format)
							{
							case IMG_FORMAT_DXT1:
								compressed_size = CompressedBlockSizeDXT1(iwi_header->dimensions[0], iwi_header->dimensions[1]);
								break;
							case IMG_FORMAT_DXT3:
							case IMG_FORMAT_DXT5:
								compressed_size = CompressedBlockSizeDXT5(iwi_header->dimensions[0], iwi_header->dimensions[1]);
								break;
							}
							unsigned int data_to_skip_size = iwi_header->fileSizeForPicmip[0] - compressed_size - sizeof(iw5::GfxImageFileHeader);

							if (data_to_skip_size >= bytes.size() - sizeof(iw5::GfxImageFileHeader))
							{
								ZONETOOL_FATAL("Something went horribly wrong parsing IWI file \"%s.iwi\"", name.data());
							}

							pixel_data = bytes.data() + sizeof(iw5::GfxImageFileHeader) + data_to_skip_size;
							pixel_data_size = bytes.size() - sizeof(iw5::GfxImageFileHeader) - data_to_skip_size;
						}
						else
						{
							pixel_data = bytes.data() + sizeof(iw5::GfxImageFileHeader);
							pixel_data_size = bytes.size() - sizeof(iw5::GfxImageFileHeader);
						}

						pixels.resize(pixel_data_size);
						memcpy(&pixels[0], pixel_data, pixel_data_size);

						// zone image
						auto* image = mem->Alloc<GfxImage>();
						image->mapType = MAPTYPE_2D;
						image->sematic = 2;
						image->category = 3;
						image->flags = 0;
						image->width = iwi_header->dimensions[0];
						image->height = iwi_header->dimensions[1];
						image->depth = iwi_header->dimensions[2];

#ifdef IMAGE_DECOMPRESS_DXT
						const unsigned int data_len = 4 * image->width * image->height;

						image->imageFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
						image->pixelData = mem->Alloc<unsigned char>(data_len);
						switch (iwi_header->format)
						{
						case IMG_FORMAT_DXT1:
							BlockDecompressImageDXT1(image->width, image->height, &pixels[0], reinterpret_cast<unsigned int*>(image->pixelData));
							break;
						case IMG_FORMAT_DXT3:
						case IMG_FORMAT_DXT5:
							BlockDecompressImageDXT5(image->width, image->height, &pixels[0], reinterpret_cast<unsigned int*>(image->pixelData));
							break;
						}
#else
						const unsigned int data_len = static_cast<unsigned int>(pixel_data_size);

						switch (iwi_header->format)
						{
						case IMG_FORMAT_DXT1:
							image->imageFormat = DXGI_FORMAT_BC1_UNORM;
							break;
						case IMG_FORMAT_DXT3:
							image->imageFormat = DXGI_FORMAT_BC2_UNORM;
							break;
						case IMG_FORMAT_DXT5:
							image->imageFormat = DXGI_FORMAT_BC3_UNORM;
							break;
						}
						image->pixelData = mem->Alloc<unsigned char>(data_len);
						memcpy(image->pixelData, pixel_data, data_len);
#endif

						image->dataLen1 = data_len;
						image->dataLen2 = data_len;

						image->numElements = 1;
						image->levelCount = 1;
						image->streamed = false;

						image->name = mem->StrDup(name);

						return image;
					}
				}
				else if (version == 6) // iw3
				{
					ZONETOOL_INFO("Parsing IWI image \"%s\", version (%i)", name.data(), version);

					std::vector<std::uint8_t> pixels;
					auto iwi_header = reinterpret_cast<iw3::GfxImageFileHeader*>(bytes.data());

					if (iwi_header->format != IMG_FORMAT_DXT1 &&
						iwi_header->format != IMG_FORMAT_DXT3 &&
						iwi_header->format != IMG_FORMAT_DXT5)
					{
						ZONETOOL_ERROR("IWI format is not DXT1, DXT3 or DXT5 for image \"%s.iwi\"", name.data());
						return nullptr;
					}

					if ((iwi_header->flags & iw3::IMG_FLAGS::IMG_FLAG_CUBEMAP) != 0) // parse cube
					{
						if (iwi_header->fileSizeForPicmip[0] > iwi_header->fileSizeForPicmip[1]) // has mipmaps
						{
							ZONETOOL_FATAL("Cube IWI \"%s\" has mipmaps...", name.data());
						}

						std::uint8_t* pixel_data = bytes.data() + sizeof(iw3::GfxImageFileHeader);
						std::size_t pixel_data_size = bytes.size() - sizeof(iw3::GfxImageFileHeader);

						// zone image
						auto* image = mem->Alloc<GfxImage>();
						image->mapType = MAPTYPE_CUBE;
						image->sematic = 2;
						image->category = 3;
						image->flags = 2;
						image->width = iwi_header->dimensions[0];
						image->height = iwi_header->dimensions[1];
						image->depth = iwi_header->dimensions[2];

						const unsigned int data_len = static_cast<unsigned int>(pixel_data_size);

						switch (iwi_header->format)
						{
						case IMG_FORMAT_DXT1:
							image->imageFormat = DXGI_FORMAT_BC1_UNORM;
							break;
						case IMG_FORMAT_DXT3:
							image->imageFormat = DXGI_FORMAT_BC2_UNORM;
							break;
						case IMG_FORMAT_DXT5:
							image->imageFormat = DXGI_FORMAT_BC3_UNORM;
							break;
						}
						image->pixelData = mem->Alloc<unsigned char>(data_len);
						memcpy(image->pixelData, pixel_data, data_len);

						image->dataLen1 = data_len;
						image->dataLen2 = data_len;

						image->numElements = 1;
						image->levelCount = 1;
						image->streamed = false;

						image->name = mem->StrDup(name);

						return image;
					}
					else // parse 2d
					{
						std::uint8_t* pixel_data;
						std::size_t pixel_data_size = 0;
						if (iwi_header->fileSizeForPicmip[0] > iwi_header->fileSizeForPicmip[1]) // has mipmaps
						{
							unsigned int compressed_size = 0;
							switch (iwi_header->format)
							{
							case IMG_FORMAT_DXT1:
								compressed_size = CompressedBlockSizeDXT1(iwi_header->dimensions[0], iwi_header->dimensions[1]);
								break;
							case IMG_FORMAT_DXT3:
							case IMG_FORMAT_DXT5:
								compressed_size = CompressedBlockSizeDXT5(iwi_header->dimensions[0], iwi_header->dimensions[1]);
								break;
							}
							unsigned int data_to_skip_size = iwi_header->fileSizeForPicmip[0] - compressed_size - sizeof(iw3::GfxImageFileHeader);

							if (data_to_skip_size >= bytes.size() - sizeof(iw3::GfxImageFileHeader))
							{
								ZONETOOL_FATAL("Something went horribly wrong parsing IWI file \"%s.iwi\"", name.data());
							}

							pixel_data = bytes.data() + sizeof(iw3::GfxImageFileHeader) + data_to_skip_size;
							pixel_data_size = bytes.size() - sizeof(iw3::GfxImageFileHeader) - data_to_skip_size;
						}
						else
						{
							pixel_data = bytes.data() + sizeof(iw3::GfxImageFileHeader);
							pixel_data_size = bytes.size() - sizeof(iw3::GfxImageFileHeader);
						}

						pixels.resize(pixel_data_size);
						memcpy(&pixels[0], pixel_data, pixel_data_size);

						// zone image
						auto* image = mem->Alloc<GfxImage>();
						image->mapType = MAPTYPE_2D;
						image->sematic = 2;
						image->category = 3;
						image->flags = 0;
						image->width = iwi_header->dimensions[0];
						image->height = iwi_header->dimensions[1];
						image->depth = iwi_header->dimensions[2];

#ifdef IMAGE_DECOMPRESS_DXT
						const unsigned int data_len = 4 * image->width * image->height;

						image->imageFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
						image->pixelData = mem->Alloc<unsigned char>(data_len);
						switch (iwi_header->format)
						{
						case IMG_FORMAT_DXT1:
							BlockDecompressImageDXT1(image->width, image->height, &pixels[0], reinterpret_cast<unsigned int*>(image->pixelData));
							break;
						case IMG_FORMAT_DXT3:
						case IMG_FORMAT_DXT5:
							BlockDecompressImageDXT5(image->width, image->height, &pixels[0], reinterpret_cast<unsigned int*>(image->pixelData));
							break;
						}
#else
						const unsigned int data_len = static_cast<unsigned int>(pixel_data_size);

						switch (iwi_header->format)
						{
						case IMG_FORMAT_DXT1:
							image->imageFormat = DXGI_FORMAT_BC1_UNORM;
							break;
						case IMG_FORMAT_DXT3:
							image->imageFormat = DXGI_FORMAT_BC2_UNORM;
							break;
						case IMG_FORMAT_DXT5:
							image->imageFormat = DXGI_FORMAT_BC3_UNORM;
							break;
						}
						image->pixelData = mem->Alloc<unsigned char>(data_len);
						memcpy(image->pixelData, pixel_data, data_len);
#endif

						image->dataLen1 = data_len;
						image->dataLen2 = data_len;

						image->numElements = 1;
						image->levelCount = 1;
						image->streamed = false;

						image->name = mem->StrDup(name);

						return image;
					}
				}
				else
				{
					ZONETOOL_ERROR("Unknown IWI version (%i) for image \"%s.iwi\"", static_cast<int>(version), name.data());
				}
			}
			return nullptr;
		}
	}

	namespace directxtex
	{
		bool load_image(const std::string& name, DirectX::ScratchImage* image)
		{
			std::string c_name = clean_name(name);
			c_name = utils::string::va("images\\%s", c_name.data());
			if (filesystem::file(c_name + ".dds").exists())
			{
				// DDS Found
				c_name.append(".dds");
			}
			else if (filesystem::file(c_name + ".tga").exists())
			{
				// TGA Found
				c_name.append(".tga");
			}
			else
			{
				// No image found
				return false;
			}
			std::string path = filesystem::get_file_path(c_name) + c_name;

			std::wstring wname = utils::string::convert(path);

			HRESULT hr = E_FAIL;
			if (c_name.ends_with(".dds"))
			{
				hr = LoadFromDDSFile(wname.data(), DirectX::DDS_FLAGS_NONE, nullptr, *image);
			}
			else if (c_name.ends_with(".tga"))
			{
				hr = LoadFromTGAFile(wname.data(), nullptr, *image);
			}

			if (SUCCEEDED(hr))
			{
				return true;
			}
			return false;
		}

		GfxImage* parse(const std::string& name, ZoneMemory* mem)
		{
			DirectX::ScratchImage image;
			bool result;
			int x;
			char m_name[128];

			x = 1024;
			result = true;
			if (!load_image(name, &image))
			{
				result = false;
				do
				{
					snprintf(m_name, sizeof(m_name), "%s_%dx%d", name.data(), x, x);
					if (load_image(m_name, &image))
					{
						result = true;
						break;
					}
					x = x / 2;
				} while (x > 0);
			}

			if (result)
			{
				ZONETOOL_INFO("Parsing custom image \"%s\"", name.data());

				auto* pixels = image.GetPixels();
				auto pixels_size = image.GetPixelsSize();
				const auto& metadata = image.GetMetadata();

				auto* gfx_image = mem->Alloc<GfxImage>();

				gfx_image->imageFormat = metadata.format;
				gfx_image->mapType = static_cast<MapType>(metadata.dimension);
				gfx_image->sematic = 2;
				gfx_image->category = 3;
				gfx_image->flags = 0;
				gfx_image->width = static_cast<unsigned short>(metadata.width);
				gfx_image->height = static_cast<unsigned short>(metadata.height);
				gfx_image->depth = static_cast<unsigned short>(metadata.depth);
				gfx_image->numElements = 1;
				gfx_image->levelCount = 1;
				gfx_image->streamed = 0;
				gfx_image->dataLen1 = static_cast<int>(pixels_size);
				gfx_image->dataLen2 = static_cast<int>(pixels_size);
				gfx_image->pixelData = mem->Alloc<unsigned char>(pixels_size);
				memcpy(gfx_image->pixelData, pixels, pixels_size);
				gfx_image->name = mem->StrDup(name);

				return gfx_image;
			}

			return nullptr;
		}
	}

	GfxImage* IGfxImage::parse_custom(const std::string& name, ZoneMemory* mem)
	{
		GfxImage* image = nullptr;
		image = directxtex::parse(name, mem);
		if (!image)
		{
			image = iwi::parse(name, mem);
		}

		return image;
	}

	GfxImage* IGfxImage::parse(const std::string& name, ZoneMemory* mem)
	{
		auto path = "images\\" + clean_name(name) + ".h1Image";

		assetmanager::reader read(mem);
		if (!read.open(path))
		{
			return nullptr;
		}

		ZONETOOL_INFO("Parsing image \"%s\"...", name.data());

		auto asset = read.read_single<GfxImage>();
		asset->name = read.read_string();
		if (asset->pixelData)
		{
			asset->pixelData = read.read_array<unsigned char>();
		}

		if (asset->streamed)
		{
			// read stream file
			for (auto i = 0u; i < 4; i++)
			{
				this->image_stream_files[i] = read.read_single<XStreamFile>();
			}
		}

		read.close();

		return asset;
	}

	void IGfxImage::init(const std::string& name, ZoneMemory* mem)
	{
		this->name_ = name;
		this->asset_ = this->parse(name, mem);

		if (!this->asset_)
		{
			this->asset_ = parse_custom(name.data(), mem);
			if (!this->asset_)
			{
				this->asset_ = DB_FindXAssetHeader_Safe(XAssetType(this->type()), this->name_.data()).image;

				if (this->asset_->streamed || (this->asset_->width == 1 && this->asset_->height == 1))
				{
					//ZONETOOL_WARNING("Image '%s' not found, it will probably look messed up ingame!", name.data());
					this->asset_->streamed = 0;
				}
			}
		}
	}

	void IGfxImage::init(void* asset, ZoneMemory* mem)
	{
		this->asset_ = reinterpret_cast<GfxImage*>(asset);
		this->name_ = this->asset_->name;

		auto parsed = this->parse(this->name_, mem);
		if (parsed)
		{
			this->asset_ = parsed;
		}
	}

	void IGfxImage::prepare(ZoneBuffer* buf, ZoneMemory* mem)
	{
	}

	void IGfxImage::load_depending(IZone* zone)
	{
	}

	std::string IGfxImage::name()
	{
		return this->name_;
	}

	std::int32_t IGfxImage::type()
	{
		return ASSET_TYPE_IMAGE;
	}

	void IGfxImage::write(IZone* zone, ZoneBuffer* buf)
	{
		auto data = this->asset_;
		auto dest = buf->write(data);

		buf->push_stream(3);

		dest->name = buf->write_str(this->name());

		if (data->sematic != 11)
		{
			buf->push_stream(0);
			if (data->pixelData)
			{
				buf->align(3);

				buf->write_stream(data->pixelData, data->dataLen1);

				ZoneBuffer::clear_pointer(&dest->pixelData);
			}
			buf->pop_stream();
		}

		buf->pop_stream();

		if (data->streamed)
		{
			// add stream file to header
			for (auto i = 0u; i < 4; i++)
			{
				buf->write_streamfile(reinterpret_cast<std::uintptr_t>(this->image_stream_files[i]));
			}
		}
	}

#ifdef IMAGE_DUMP_DDS
	void dump_image_dds(GfxImage* image)
	{
		if (!image->streamed)
		{
			DirectX::Image img = {};
			img.pixels = image->pixelData;
			img.width = image->width;
			img.height = image->height;
			img.format = DXGI_FORMAT(image->imageFormat);

			size_t rowPitch;
			size_t slicePitch;
			DirectX::ComputePitch(img.format, img.width, img.height, rowPitch, slicePitch);

			img.rowPitch = rowPitch;
			img.slicePitch = slicePitch;

			std::string parent_path = filesystem::get_dump_path() + "images\\";
			std::string spath = parent_path + clean_name(image->name) + ".dds";
			std::wstring wpath(spath.begin(), spath.end());

			if (!std::filesystem::exists(parent_path))
			{
				std::filesystem::create_directories(parent_path);
			}

			auto result = DirectX::SaveToDDSFile(img, DirectX::DDS_FLAGS_NONE, wpath.data());
			if (FAILED(result))
			{
				ZONETOOL_WARNING("Failed to dump image \"%s.dds\"", image->name);
			}
		}
	}
#endif

	void IGfxImage::dump(GfxImage* asset)
	{
#ifdef IMAGE_DUMP_DDS
		dump_image_dds(asset);
#endif

		auto path = "images\\"s + clean_name(asset->name) + ".h1Image"s;
		assetmanager::dumper write;
		if (!write.open(path))
		{
			return;
		}

		if (asset->sematic == 11)
		{
			ZONETOOL_WARNING("GfxImage (%s) was not dumped succesfully!", asset->name);
			write.close();
			return;
		}

		write.dump_single(asset);
		write.dump_string(asset->name);

		if (asset->pixelData)
		{
			write.dump_array(asset->pixelData, asset->dataLen1);
		}

		if (asset->streamed)
		{
			auto streamFileIndex = *reinterpret_cast<unsigned int*>(0x143274884);
			auto streamFiles = reinterpret_cast<XStreamFile*>(0x1432748B0);

			for (auto i = 0u; i < 4; i++)
			{
				auto streamFile = &streamFiles[streamFileIndex + i];
				write.dump_single(streamFile);
			}
		}
		write.close();
	}
}