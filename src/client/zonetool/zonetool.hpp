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

#include "assets/dopplerpreset.hpp"
#include "assets/gfximage.hpp"
#include "assets/loadedsound.hpp"
#include "assets/localize.hpp"
#include "assets/lpfcurve.hpp"
#include "assets/luafile.hpp"
#include "assets/mapents.hpp"
#include "assets/material.hpp"
#include "assets/rawfile.hpp"
#include "assets/netconststrings.hpp"
#include "assets/rawfile.hpp"
#include "assets/reverbcurve.hpp"
#include "assets/scriptfile.hpp"
#include "assets/sound.hpp"
#include "assets/soundcontext.hpp"
#include "assets/soundcurve.hpp"
#include "assets/stringtable.hpp"
#include "assets/structureddatadefset.hpp"
#include "assets/techset.hpp"
#include "assets/ttf.hpp"

#include "assets/computeshader.hpp"
#include "assets/domainshader.hpp"
#include "assets/hullshader.hpp"
#include "assets/pixelshader.hpp"
#include "assets/vertexdecl.hpp"
#include "assets/vertexshader.hpp"

#include "zone.hpp"

namespace zonetool
{
	void initialize();
	void start();
}