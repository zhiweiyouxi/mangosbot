#pragma once

#define GLOBAL_COOLDOWN 2
#define BOT_REACT_DELAY 1

#define BOTLOOT_DISTANCE 25.0f
#define EAT_DRINK_PERCENT 40
#define SPELL_DISTANCE 25.0f
#define BOT_REACT_DISTANCE 50.0f

std::vector<std::string> split(const std::string &s, char delim);

#include "../Spell.h"
#include "../WorldPacket.h"
#include "../LootMgr.h"
#include "../GossipDef.h"
#include "../Chat.h"
#include "../Common.h"
#include "../World.h"
#include "../SpellMgr.h"
#include "../ObjectMgr.h"
#include "../Unit.h"
#include "../SharedDefines.h"
#include "../MotionMaster.h"
#include "../SpellAuras.h"
#include "../Guild.h"

#include "ai/AiManagers.h"

#include "PlayerbotMgr.h"
#include "PlayerbotAI.h"

