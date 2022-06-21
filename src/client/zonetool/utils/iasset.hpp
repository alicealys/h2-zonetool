#pragma once
#include <std_include.hpp>

namespace zonetool
{
	class IAsset
	{
	public:
		virtual void init(const std::string& name, ZoneMemory* mem)
		{
		}

		virtual void init(void* asset, ZoneMemory* mem)
		{
		}

		virtual void prepare(ZoneBuffer* buf, ZoneMemory* mem)
		{
		}

		virtual std::string name() { return ""; }
		virtual std::int32_t type() { return -1; }
		virtual void* pointer() { return nullptr; }

		virtual void write(IZone* zone, ZoneBuffer* buffer)
		{
		}

		virtual void load_depending(IZone* zone)
		{
		}
	};
}
