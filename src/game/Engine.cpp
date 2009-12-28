#include "pchdef.h"
#include <list>
#include "Common.h"
#include "World.h"
#include "SpellMgr.h"
#include "Player.h"
#include "ObjectMgr.h"
#include "WorldPacket.h"
#include "Unit.h"
#include "SharedDefines.h"
#include "PlayerbotAI.h"

#include "Engine.h"

namespace ai
{
Engine::Engine(Player* const master, Player* const bot, PlayerbotAI* const ai)
{
	this->master = master;
	this->bot = bot;
	this->ai = ai;
}

Engine::~Engine(void)
{
	Action* action = NULL;
	do 
	{
		action = queue.Pop();
	} while (action);
	for (std::list<Trigger*>::iterator i = triggers.begin(); i != triggers.end(); i++)
	{
		Trigger* trigger = *i;
		delete trigger;
	}
	triggers.empty();
}

void Engine::DoNextAction(Unit*)
{
	for (std::list<Trigger*>::iterator i = triggers.begin(); i != triggers.end(); i++)
	{
		Trigger* trigger = *i;
		if (trigger->IsActive())
		{
			queue.Push(trigger->CreateHandlers());
		}
	}
	Action* action = queue.Pop();
	
	if (action)
	{
		action->Execute();
		queue.Push(action->GetAfterActions());
		delete action;
	}
}

}