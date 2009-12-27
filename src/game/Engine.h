#pragma once
#include "Queue.h"
#include "Common.h"
#include "World.h"
#include "SpellMgr.h"
#include "Player.h"
#include "ObjectMgr.h"
#include "WorldPacket.h"
#include "Unit.h"
#include "SharedDefines.h"
#include "PlayerbotAI.h"

namespace ai
{
class MANGOS_DLL_SPEC Engine
{
public:
	Engine(Player* const master, Player* const bot, PlayerbotAI* const ai);

	virtual void Init() {}
	virtual void DoNextAction(Unit*);

public:
	virtual ~Engine(void);
protected:
	Queue queue;
	Player* master;
	Player* bot;
	PlayerbotAI* ai;
};
}