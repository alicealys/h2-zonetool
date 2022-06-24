#include <std_include.hpp>
#include "lpfcurve.hpp"

namespace zonetool
{
	SndCurve* ILpfCurve::parse(const std::string& name, ZoneMemory* mem)
	{
		return ISoundCurve::parse(name, "lpfcurve", mem);
	}

	void ILpfCurve::init(const std::string& name, ZoneMemory* mem)
	{
		this->name_ = name;
		this->asset_ = parse(name, mem);

		if (!this->asset_)
		{
			this->asset_ = DB_FindXAssetHeader_Safe(XAssetType(this->type()), this->name().data()).sndCurve;
		}
	}

	void ILpfCurve::prepare(ZoneBuffer* buf, ZoneMemory* mem)
	{
	}

	void ILpfCurve::load_depending(IZone* zone)
	{
	}

	std::string ILpfCurve::name()
	{
		return this->name_;
	}

	std::int32_t ILpfCurve::type()
	{
		return ASSET_TYPE_LPF_CURVE;
	}

	void ILpfCurve::write(IZone* zone, ZoneBuffer* buf)
	{
		auto data = this->asset_;
		auto dest = buf->write(data);

		buf->push_stream(3);

		dest->filename = buf->write_str(this->name());

		buf->pop_stream();
	}

	void ILpfCurve::dump(SndCurve* asset)
	{
		ISoundCurve::dump(asset, "lpfcurve");
	}
}