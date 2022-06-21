#include <std_include.hpp>
#include "stringtable.hpp"

namespace zonetool
{
	// LEGACY ZONETOOL CODE, FIX ME!
	class CSV
	{
	protected:
		std::string _name;
		std::vector<std::vector<std::string>> _data;

	public:
		CSV(std::string name, char sep = ',')
			: _name(name)
		{
			auto f = filesystem::file(name);
			f.open("rb");

			auto fp = f.get_fp();

			if (fp)
			{
				auto len = f.size();
				auto buf = std::make_unique<char[]>(len + 1);
				memset(buf.get(), 0, len + 1);
				fread(buf.get(), len, 1, fp);
				fclose(fp);

				std::vector<std::string> rows = utils::string::split(std::string(buf.get()), '\n');

				for (auto& row : rows)
				{
					// Replace literal characters
					std::size_t pos;
					while ((pos = row.find("\\n")) != std::string::npos)
					{
						row.replace(pos, 2, "\n");
					}

					while ((pos = row.find("\\t")) != std::string::npos)
					{
						row.replace(pos, 2, "\t");
					}

					_data.push_back(utils::string::split(row, sep));
				}
			}

			f.close();
		}

		std::string entry(std::size_t row, std::size_t column)
		{
			return _data[row][column];
		}

		std::size_t rows()
		{
			return _data.size();
		}

		std::size_t columns(std::size_t row)
		{
			return _data[row].size();
		}

		std::size_t max_columns()
		{
			std::size_t _max = 0;

			for (std::size_t row = 0; row < this->rows(); row++)
			{
				if (_max < this->columns(row))
					_max = this->columns(row);
			}

			return _max;
		}

		void clear()
		{
			for (std::size_t i = 0; i < _data.size(); i++)
			{
				for (std::size_t j = 0; j < _data[i].size(); j++)
					_data[i][j].clear();

				_data[i].clear();
			}

			_data.clear();
		}
	};

	int StringTable_Hash(const char* string)
	{
		int hash = 0;
		char* data = _strdup(string);

		while (*data != 0)
		{
			hash = tolower(*data) + (31 * hash);
			data++;
		}

		return hash;
	}

	StringTable* StringTable_Parse(std::string name, ZoneMemory* mem)
	{
		auto table = std::make_unique<CSV>(name);
		auto stringtable = mem->Alloc<StringTable>();

		stringtable->name = mem->StrDup(name.c_str());
		stringtable->rowCount = static_cast<int>(table->rows());
		stringtable->columnCount = static_cast<int>(table->max_columns());
		stringtable->values = mem->Alloc<StringTableCell>(stringtable->rowCount * stringtable->columnCount);

		for (int row = 0; row < table->rows(); row++)
		{
			for (int col = 0; col < table->columns(row); col++)
			{
				int entry = (row * stringtable->columnCount) + col;
				stringtable->values[entry].string = mem->StrDup(table->entry(row, col).c_str());
				stringtable->values[entry].hash = StringTable_Hash(stringtable->values[entry].string);
			}
		}

		return stringtable;
	}

	void IStringTable::init(const std::string& name, ZoneMemory* mem)
	{
		this->name_ = name;
		this->asset_ = DB_FindXAssetHeader_Safe(static_cast<XAssetType>(this->type()), this->name().data()).stringTable;

		if (filesystem::file(name).exists())
		{
			ZONETOOL_INFO("Parsing stringtable \"%s\"...", name.data());
			this->asset_ = StringTable_Parse(name, mem);
		}
	}

	void IStringTable::prepare(ZoneBuffer* buf, ZoneMemory* mem)
	{
	}

	void IStringTable::load_depending(IZone* zone)
	{
	}

	std::string IStringTable::name()
	{
		return this->name_;
	}

	std::int32_t IStringTable::type()
	{
		return ASSET_TYPE_STRINGTABLE;
	}

	void IStringTable::write(IZone* zone, ZoneBuffer* buf)
	{
		auto data = this->asset_;
		auto dest = buf->write(data);

		buf->push_stream(3);

		dest->name = buf->write_str(this->name());

		if (data->values)
		{
			buf->align(3);
			const auto destStrings = buf->write(data->values, data->columnCount * data->rowCount);

			if (data->columnCount * data->rowCount > 0)
			{
				for (int i = 0; i < data->columnCount * data->rowCount; i++)
				{
					if (data->values[i].string)
					{
						destStrings[i].string = buf->write_str(data->values[i].string);
					}
				}
			}

			ZoneBuffer::clear_pointer(&dest->values);
		}

		buf->pop_stream();
	}

	void IStringTable::dump(StringTable* asset)
	{
		auto file = filesystem::file(asset->name);
		file.open("wb");

		if (file.get_fp())
		{
			for (int row = 0; row < asset->rowCount; row++)
			{
				for (int column = 0; column < asset->columnCount; column++)
				{
					fprintf(
						file.get_fp(),
						"%s%s",
						(asset->values[(row * asset->columnCount) + column].string)
						? asset->values[(row * asset->columnCount) + column].string
						: "",
						(column == asset->columnCount - 1) ? "\n" : ","
					);
				}
			}
		}

		file.close();
	}
}