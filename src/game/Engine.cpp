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
#include "PlayerbotAIFacade.h"

#include "Engine.h"

using namespace ai;
using namespace std;

Engine::~Engine(void)
{
    Reset();
}

void Engine::Reset()
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
	triggers.clear();

    for (std::list<Multiplier*>::iterator i = multipliers.begin(); i != multipliers.end(); i++)
    {
        Multiplier* multiplier = *i;
        delete multiplier;
    }
    multipliers.clear();

    if (actionFactory)
        delete actionFactory;

    if (strategy)
        delete strategy;
}

void Engine::Init(Strategy *strategy)
{
    Reset();
    this->strategy = strategy;
    this->actionFactory = strategy->createActionFactory();

    strategy->InitMultipliers(multipliers);
    strategy->InitTriggers(triggers);
    MultiplyAndPush(strategy->getNextActions());
}


BOOL Engine::DoNextAction(Unit* unit)
{
    BOOL actionExecuted = FALSE;

	for (std::list<Trigger*>::iterator i = triggers.begin(); i != triggers.end(); i++)
	{
		Trigger* trigger = *i;
		if (trigger->IsActive())
		{
			MultiplyAndPush(trigger->getNextActions());
		}
	}
    Action* action = NULL;
    
    do 
    {
        action = queue.Pop();
        if (action)
        {
            if (action->isAvailable())
            {
                action->Execute();
                MultiplyAndPush(action->getNextActions());
                actionExecuted = TRUE;
                delete action;
                break;
            }
            delete action;
        }
    }
    while (action);
	
    if (!action)
    {
        MultiplyAndPush(strategy->getNextActions());
    }

    return actionExecuted;
}

void Engine::MultiplyAndPush(NextAction** actions)
{
    if (actions)
    {
        for (int j=0; j<10; j++) // TODO: remove 10
        {
            NextAction* nextAction = actions[j];
            if (nextAction)
            {
                Action* action = actionFactory->createAction(nextAction->getName());
                float k = nextAction->getRelevance();
                for (std::list<Multiplier*>::iterator i = multipliers.begin(); i!= multipliers.end(); i++)
                {
                    Multiplier* multiplier = *i;
                    k *= multiplier->GetValue(action);
                }

                queue.Push(new ActionBasket(action, k));
                delete nextAction;
            }
            else 
                break;
        }
        delete actions;
    }
}

void Engine::ExecuteAction(const char* name)
{
    Action *action = actionFactory->createAction(name);
    if (action)
    {
        action->Execute();
        MultiplyAndPush(action->getNextActions());
        delete action;
    }
}
