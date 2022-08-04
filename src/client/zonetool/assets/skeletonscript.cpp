#include "std_include.hpp"
#include "skeletonscript.hpp"

namespace zonetool
{
	void ISkeletonScript::add_script_string(scr_string_t* ptr, std::string str)
	{
		for (std::uint32_t i = 0; i < this->script_strings.size(); i++)
		{
			if (this->script_strings[i].first == ptr)
			{
				return;
			}
		}
		this->script_strings.push_back(std::pair<scr_string_t*, std::string>(ptr, str));
	}

	std::string ISkeletonScript::get_script_string(scr_string_t* ptr)
	{
		for (std::uint32_t i = 0; i < this->script_strings.size(); i++)
		{
			if (this->script_strings[i].first == ptr)
			{
				return this->script_strings[i].second;
			}
		}
		return "";
	}

	void ISkeletonScript::init(const std::string& name, ZoneMemory* mem)
	{
		this->name_ = name;

		if (this->referenced())
		{
			this->asset_ = mem->Alloc<typename std::remove_reference<decltype(*this->asset_)>::type>();
			this->asset_->name = mem->StrDup(name);
			return;
		}

		this->asset_ = DB_FindXAssetHeader_Safe(XAssetType(this->type()), this->name().data()).skeletonScript;
		for (unsigned char i = 0; i < this->asset_->ikData->stringsCount; i++)
		{
			this->add_script_string(&this->asset_->ikData->strings[i], SL_ConvertToString(this->asset_->ikData->strings[i]));
		}
	}

	void ISkeletonScript::prepare(ZoneBuffer* buf, ZoneMemory* mem)
	{
		auto* data = this->asset_;

		for (unsigned char i = 0; i < data->ikData->stringsCount; i++)
		{
			auto str = this->get_script_string(&data->ikData->strings[i]);
			data->ikData->strings[i] = static_cast<scr_string_t>(buf->write_scriptstring(str));
		}
	}

	void ISkeletonScript::load_depending(IZone* zone)
	{
	}

	std::string ISkeletonScript::name()
	{
		return this->name_;
	}

	std::int32_t ISkeletonScript::type()
	{
		return ASSET_TYPE_SKELETONSCRIPT;
	}

	void ISkeletonScript::write(IZone* zone, ZoneBuffer* buf)
	{
		auto data = this->asset_;
		auto dest = buf->write(data);

		buf->push_stream(3);

		dest->name = buf->write_str(this->name());

		if (data->ikData->charData)
		{
			buf->align(0);
			buf->write(data->ikData->charData, data->ikData->charDataLen);
			ZoneBuffer::clear_pointer(&dest->ikData->charData);
		}

		if (data->ikData->charData)
		{
			buf->align(0);
			buf->write(data->ikData->charData, data->ikData->charDataLen);
			ZoneBuffer::clear_pointer(&dest->ikData->charData);
		}

		if (data->ikData->floatData)
		{
			buf->align(3);
			buf->write(data->ikData->floatData, data->ikData->floatDataLen);
			ZoneBuffer::clear_pointer(&dest->ikData->floatData);
		}

		if (data->ikData->int32Data)
		{
			buf->align(3);
			buf->write(data->ikData->int32Data, data->ikData->int32DataLen);
			ZoneBuffer::clear_pointer(&dest->ikData->int32Data);
		}

		if (data->ikData->strings)
		{
			buf->align(3);
			buf->write(data->ikData->strings, data->ikData->stringsCount);
			ZoneBuffer::clear_pointer(&dest->ikData->strings);
		}

		buf->pop_stream();
	}

	void ISkeletonScript::dump(SkeletonScript* asset)
	{
	}
}