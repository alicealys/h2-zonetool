#include "std_include.hpp"
#include "physworld.hpp"

namespace zonetool
{
	void IPhysWorld::add_script_string(scr_string_t* ptr, std::string str)
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

	std::string IPhysWorld::get_script_string(scr_string_t* ptr)
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

	void IPhysWorld::init(const std::string& name, ZoneMemory* mem)
	{
		this->name_ = name;

		if (this->referenced())
		{
			this->asset_ = mem->Alloc<typename std::remove_reference<decltype(*this->asset_)>::type>();
			this->asset_->name = mem->StrDup(name);
			return;
		}

		this->asset_ = DB_FindXAssetHeader_Copy<PhysWorld>(XAssetType(this->type()), this->name().data(), mem).physWorld;
		if (this->asset_->waterVolumes)
		{
			auto* original_water_volumes = this->asset_->waterVolumes;
			this->asset_->waterVolumes = mem->Alloc<PhysWaterVolumeDef>(this->asset_->waterVolumesCount);
			memcpy(this->asset_->waterVolumes, original_water_volumes, sizeof(PhysWaterVolumeDef) * this->asset_->waterVolumesCount);
			for (unsigned int i = 0; i < this->asset_->waterVolumesCount; i++)
			{
				this->add_script_string(&this->asset_->waterVolumes[i].string, SL_ConvertToString(original_water_volumes[i].string));
			}
		}
	}

	void IPhysWorld::prepare(ZoneBuffer* buf, ZoneMemory* mem)
	{
		auto* data = this->asset_;

		if (data->waterVolumes)
		{
			for (unsigned int i = 0; i < data->waterVolumesCount; i++)
			{
				auto str = this->get_script_string(&data->waterVolumes[i].string);
				data->waterVolumes[i].string = static_cast<scr_string_t>(buf->write_scriptstring(str));
			}
		}
	}

	void IPhysWorld::load_depending(IZone* zone)
	{
		for (unsigned int i = 0; i < this->asset_->waterVolumesCount; i++)
		{
			zone->add_asset_of_type(ASSET_TYPE_PHYSWATERPRESET, this->asset_->waterVolumes[i].physWaterPreset->name);
		}
	}

	std::string IPhysWorld::name()
	{
		return this->name_;
	}

	std::int32_t IPhysWorld::type()
	{
		return ASSET_TYPE_PHYSWORLDMAP;
	}

	void IPhysWorld::write(IZone* zone, ZoneBuffer* buf)
	{
		auto data = this->asset_;
		auto dest = buf->write(data);

		buf->push_stream(3);

		dest->name = buf->write_str(this->name());

		if (data->models)
		{
			buf->align(3);
			buf->write(data->models, data->modelsCount);
			ZoneBuffer::clear_pointer(&dest->models);
		}

		if (data->polytopeDatas)
		{
			buf->align(3);
			auto* dest_poly_datas = buf->write(data->polytopeDatas, data->polytopeDatasCount);
			for (unsigned int i = 0; i < data->polytopeDatasCount; i++)
			{
				auto* data_poly_data = &data->polytopeDatas[i];
				auto* dest_poly_data = &dest_poly_datas[i];

				if (data_poly_data->vec4_array0)
				{
					buf->align(15);
					buf->write(data_poly_data->vec4_array0, data_poly_data->count0);
					ZoneBuffer::clear_pointer(&dest_poly_data->vec4_array0);
				}

				if (data_poly_data->vec4_array1)
				{
					buf->align(15);
					buf->write(data_poly_data->vec4_array1, data_poly_data->count1);
					ZoneBuffer::clear_pointer(&dest_poly_data->vec4_array1);
				}

				if (data_poly_data->edges)
				{
					buf->align(3);
					buf->write(data_poly_data->edges, data_poly_data->count2);
					ZoneBuffer::clear_pointer(&dest_poly_data->edges);
				}

				if (data_poly_data->uint8_array0)
				{
					buf->align(0);
					buf->write(data_poly_data->uint8_array0, data_poly_data->count1);
					ZoneBuffer::clear_pointer(&dest_poly_data->uint8_array0);
				}

				if (data_poly_data->uint16_array0)
				{
					buf->align(1);
					buf->write(data_poly_data->uint16_array0, data_poly_data->count1);
					ZoneBuffer::clear_pointer(&dest_poly_data->uint16_array0);
				}

				if (data_poly_data->uint16_array1)
				{
					buf->align(1);
					buf->write(data_poly_data->uint16_array1, data_poly_data->count0);
					ZoneBuffer::clear_pointer(&dest_poly_data->uint16_array1);
				}
			}
			ZoneBuffer::clear_pointer(&dest->polytopeDatas);
		}

		if (data->meshDatas)
		{
			buf->align(3);
			auto* dest_mesh_datas = buf->write(data->meshDatas, data->meshDatasCount);
			for (unsigned int i = 0; i < data->meshDatasCount; i++)
			{
				auto* data_mesh_data = &data->meshDatas[i];
				auto* dest_mesh_data = &dest_mesh_datas[i];

				if (data_mesh_data->meshNodes)
				{
					buf->align(15);
					buf->write(data_mesh_data->meshNodes, data_mesh_data->count0);
					ZoneBuffer::clear_pointer(&dest_mesh_data->meshNodes);
				}

				if (data_mesh_data->vec4_array0)
				{
					buf->align(15);
					buf->write(data_mesh_data->vec4_array0, data_mesh_data->count1);
					ZoneBuffer::clear_pointer(&dest_mesh_data->vec4_array0);
				}

				if (data_mesh_data->meshTriangles)
				{
					buf->align(3);
					buf->write(data_mesh_data->meshTriangles, data_mesh_data->count2);
					ZoneBuffer::clear_pointer(&dest_mesh_data->meshTriangles);
				}
			}
			ZoneBuffer::clear_pointer(&dest->meshDatas);
		}

		if (data->waterVolumes)
		{
			buf->align(3);
			auto* dest_waterVolumes = buf->write(data->waterVolumes, data->waterVolumesCount);
			for (unsigned int i = 0; i < data->waterVolumesCount; i++)
			{
				auto* data_waterVolume = &data->waterVolumes[i];
				auto* dest_waterVolume = &dest_waterVolumes[i];

				if (data_waterVolume->physWaterPreset)
				{
					dest_waterVolume->physWaterPreset = reinterpret_cast<PhysWaterPreset*>(
						zone->get_asset_pointer(ASSET_TYPE_PHYSWATERPRESET, data->waterVolumes->physWaterPreset->name));
				}
			}
			ZoneBuffer::clear_pointer(&dest->waterVolumes);
		}
		buf->pop_stream();
	}

	void IPhysWorld::dump(PhysWorld* asset)
	{
	}
}