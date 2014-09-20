#pragma once

std::vector<std::string> split(const std::string &s, char delim);
#ifndef WIN32
int strcmpi(std::string s1, std::string s2);
#endif

#include "../game/Spell.h"
#include "../../src/shared/WorldPacket.h"
#include "../game/LootMgr.h"
#include "../game/GossipDef.h"
#include "../game/Chat.h"
#include "../../../src/shared/Common.h"
#include "../game/World.h"
#include "../game/SpellMgr.h"
#include "../game/ObjectMgr.h"
#include "../game/Unit.h"
#include "../game/SharedDefines.h"
#include "../game/MotionMaster.h"
#include "../game/SpellAuras.h"
#include "../game/Guild.h"

#include "playerbotDefs.h"
#include "PlayerbotAIAware.h"
#include "PlayerbotMgr.h"
#include "RandomPlayerbotMgr.h"
#include "ChatHelper.h"
#include "PlayerbotAI.h"
