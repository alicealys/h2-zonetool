#pragma once
#include "../zonetool.hpp"

namespace zonetool
{
	class IDopplerPreset : public IAsset
	{
	private:
		std::string name_;
		DopplerPreset* asset_ = nullptr;

	public:
		DopplerPreset* parse(const std::string& name, ZoneMemory* mem);

		void init(const std::string& name, ZoneMemory* mem) override;
		void prepare(ZoneBuffer* buf, ZoneMemory* mem) override;
		void load_depending(IZone* zone) override;

		std::string name() override;
		std::int32_t type() override;
		void* pointer() override;
		void write(IZone* zone, ZoneBuffer* buffer) override;

		static void dump(DopplerPreset* asset);
	};
}