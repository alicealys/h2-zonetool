#include <std_include.hpp>
#include "reverbcurve.hpp"

namespace zonetool
{
	SndCurve* IReverbCurve::parse(const std::string& name, ZoneMemory* mem)
	{
		return ISoundCurve::parse(name, "reverbsendcurve", mem);
	}

	void IReverbCurve::init(const std::string& name, ZoneMemory* mem)
	{
		this->name_ = name;
		this->asset_ = parse(name, mem);

		if (!this->asset_)
		{
			this->asset_ = DB_FindXAssetHeader_Safe(XAssetType(this->type()), this->name().data()).sndCurve;
		}
	}

	void IReverbCurve::prepare(ZoneBuffer* buf, ZoneMemory* mem)
	{
	}

	void IReverbCurve::load_depending(IZone* zone)
	{
	}

	std::string IReverbCurve::name()
	{
		return this->name_;
	}

	std::int32_t IReverbCurve::type()
	{
		return ASSET_TYPE_REVERB_CURVE;
	}

	void IReverbCurve::write(IZone* zone, ZoneBuffer* buf)
	{
		auto data = this->asset_;
		auto dest = buf->write(data);

		buf->push_stream(3);

		dest->filename = buf->write_str(this->name());

		buf->pop_stream();
	}

	void IReverbCurve::dump(SndCurve* asset)
	{
		ISoundCurve::dump(asset, "reverbsendcurve");
	}
}