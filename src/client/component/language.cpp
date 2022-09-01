#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include "game/game.hpp"
#include "game/dvars.hpp"

#include <utils/hook.hpp>
#include <utils/io.hpp>

#define LANGUAGE_FILE "players2/default/language"

namespace language
{
	namespace
	{
		const char* get_loc_language_string()
		{
			if (!utils::io::file_exists(LANGUAGE_FILE))
			{
				return nullptr;
			}

			static char language[0x200] = {0};
			const auto data = utils::io::read_file(LANGUAGE_FILE);
			strcpy_s(language, data.data());
			return language;
		}
	}

	class component final : public component_interface
	{
	public:
		void post_unpack() override
		{
			utils::hook::call(0x14060AFFB, get_loc_language_string);
		}
	};
}

REGISTER_COMPONENT(language::component)
