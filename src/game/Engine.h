#pragma once

#include "Action.h"
#include "Queue.h"
#include "Trigger.h"

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
	std::list<Trigger*> triggers;
	Player* master;
	Player* bot;
	PlayerbotAI* ai;
};
}