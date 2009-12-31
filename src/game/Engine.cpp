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
    clearStrategies();
    if (actionFactory)
        delete actionFactory;
    if (ai)
        delete ai;
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
}

void Engine::clearStrategies()
{
    for (std::list<Strategy*>::iterator i = strategies.begin(); i != strategies.end(); i++)
    {
        Strategy* strategy = *i;
        delete strategy;
    }
    strategies.clear();
}

void Engine::Init()
{
    Reset();

    for (std::list<Strategy*>::iterator i = strategies.begin(); i != strategies.end(); i++)
    {
        Strategy* strategy = *i;
        strategy->InitMultipliers(multipliers);
        strategy->InitTriggers(triggers);
        MultiplyAndPush(strategy->getNextActions());
    }
}


BOOL Engine::DoNextAction(Unit* unit)
{
    BOOL actionExecuted = FALSE;

	for (std::list<Trigger*>::iterator i = triggers.begin(); i != triggers.end(); i++)
	{
		Trigger* trigger = *i;
		if (trigger->IsActive())
		{
            sLog.outBasic("T:%s", trigger->getName());
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
                sLog.outBasic("A:%s", action->getName());
                action->Execute();
                MultiplyAndPush(action->getNextActions());
                actionExecuted = TRUE;
                delete action;
                break;
            }
            else
            {
                sLog.outBasic("A:%s - n/a", action->getName());
                MultiplyAndPush(action->getAlternativeActions());
            }
            delete action;
        }
    }
    while (action);
	
    if (!action)
    {
        sLog.outBasic("--- queue is empty ---");
        for (std::list<Strategy*>::iterator i = strategies.begin(); i != strategies.end(); i++)
        {
            Strategy* strategy = *i;
            MultiplyAndPush(strategy->getNextActions());
        }
        return DoNextAction(unit);
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

void Engine::addStrategy(const char* name)
{
    removeStrategy(name);
    strategies.push_back(actionFactory->createStrategy(name));
}

void Engine::removeStrategy(const char* name)
{
    for (std::list<Strategy*>::iterator i = strategies.begin(); i != strategies.end(); i++)
    {
        Strategy* strategy = *i;
        if (!strcmp(strategy->getName(), name))
        {
            strategies.remove(strategy);
            delete strategy;
        }
    }
}
