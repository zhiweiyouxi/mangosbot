#pragma once

std::vector<std::string> split(const std::string &s, char delim);
#ifndef WIN32
int strcmpi(const char *s1, const char *s2);
#endif

#include "../Spell.h"
#include "../../../src/shared/WorldPacket.h"
#include "../LootMgr.h"
#include "../GossipDef.h"
#include "../Chat.h"
#include "../../../src/shared/Common.h"
#include "../World.h"
#include "../SpellMgr.h"
#include "../ObjectMgr.h"
#include "../Unit.h"
#include "../SharedDefines.h"
#include "../MotionMaster.h"
#include "../SpellAuras.h"
#include "../Guild.h"

#include "playerbotDefs.h"
#include "ai/AiManagers.h"

#include "PlayerbotMgr.h"
#include "PlayerbotAI.h"
