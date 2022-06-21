#pragma once

#include <utils/hook.hpp>
#include <utils/string.hpp>
#include "game/game.hpp"
#include "component/command.hpp"
#include "component/scheduler.hpp"

#include "structs.hpp"
#include "functions.hpp"
#include "variables.hpp"

#include "utils/utils.hpp"

#include "assets/localize.hpp"
#include "assets/luafile.hpp"
#include "assets/rawfile.hpp"
#include "assets/netconststrings.hpp"
#include "assets/rawfile.hpp"
#include "assets/scriptfile.hpp"
#include "assets/stringtable.hpp"
#include "assets/ttf.hpp"

#include "zone.hpp"

namespace zonetool
{
	void initialize();
	void start();
}