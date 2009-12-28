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

using namespace ai;

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

    for (std::list<Multiplier*>::iterator i = multipliers.begin(); i != multipliers.end(); i++)
    {
        Multiplier* multiplier = *i;
        delete multiplier;
    }
    multipliers.empty();
}

void Engine::DoNextAction(Unit*)
{
	for (std::list<Trigger*>::iterator i = triggers.begin(); i != triggers.end(); i++)
	{
		Trigger* trigger = *i;
		if (trigger->IsActive())
		{
			MultiplyAndPush(trigger->CreateHandlers());
		}
	}
	Action* action = queue.Pop();
	
	if (action)
	{
		action->Execute();
		MultiplyAndPush(action->GetAfterActions());
		delete action;
	}
}

void Engine::MultiplyAndPush(ActionBasket** actions)
{
    if (actions)
    {
        for (std::list<Multiplier*>::iterator i = multipliers.begin(); i!= multipliers.end(); i++)
        {
            Multiplier* multiplier = *i;
            for (int j=0; j<sizeof(actions)/sizeof(ActionBasket*); j++)
            {
                float k = multiplier->GetValue(actions[j]->getAction());
                actions[j]->AmendRelevance(k);
            }
        }
        queue.Push(actions);
    }
}
