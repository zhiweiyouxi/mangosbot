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

bool ActionExecutionListeners::ActionExecuted(Action* action)
{
    bool result = true;
    for (std::list<ActionExecutionListener*>::iterator i = listeners.begin(); i!=listeners.end(); i++)
    {
        result &= (*i)->ActionExecuted(action);
    }
    return result;
}

ActionExecutionListeners::~ActionExecutionListeners()
{
    for (std::list<ActionExecutionListener*>::iterator i = listeners.begin(); i!=listeners.end(); i++)
    {
        delete *i;
    }
    listeners.clear();
}


Engine::~Engine(void)
{
    Reset();
    clearStrategies();
    if (actionFactory)
        delete actionFactory;
}

void Engine::Reset()
{
	ActionNode* action = NULL;
	do 
	{
		action = queue.Pop();
	} while (action);
	
    for (std::list<TriggerNode*>::iterator i = triggers.begin(); i != triggers.end(); i++)
	{
		TriggerNode* trigger = *i;
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
        MultiplyAndPush(strategy->getDefaultActions());
    }
}


BOOL Engine::DoNextAction(Unit* unit, int depth)
{
    BOOL actionExecuted = FALSE;
    ActionBasket* basket = NULL;

    ProcessTriggers();

    do 
    {
        basket = queue.Peek();
        if (basket)
        {
            float relevance = basket->getRelevance(); // just for reference
            BOOL skipPrerequisites = basket->isSkipPrerequisites();
            ActionNode* action = queue.Pop();

            if (action->isPossible())
            {
                if (action->isUseful())
                {
                    if ((!skipPrerequisites || lastRelevance-relevance > 0.02) && MultiplyAndPush(action->getPrerequisites(), relevance + 0.01))
                    {
                        //sLog.outBasic("A:%s - prerequisites", action->getName());
                        NextAction** prerequisites = new NextAction*[2];
                        prerequisites[0] = new NextAction(action->getName(), relevance);
                        prerequisites[1] = NULL;
                        MultiplyAndPush(prerequisites, relevance, TRUE);
                        delete action;
                        continue;
                        //if (depth < 5)
                        //    DoNextAction(unit, depth + 1);
                        //break;
                    }

                    sLog.outBasic("A:%s", action->getName());

                    if (actionExecutionListeners.ActionExecuted(action->getAction()))
                    {
                        actionExecuted = action->Execute();
                    }

                    if (actionExecuted)
                    {
                        MultiplyAndPush(action->getContinuers());
                        lastRelevance = relevance;
                        delete action;
                        break;
                    }
                    else
                    {
                        MultiplyAndPush(action->getAlternatives(), relevance);
                    }
                }
                else
                {
                    lastRelevance = relevance;
                    //sLog.outBasic("A:%s - useless", action->getName());
                }
            }
            else 
            {
                //sLog.outBasic("A:%s - n/a", action->getName());
                if (action->isUseful())
                    MultiplyAndPush(action->getAlternatives(), relevance);
                else
                    lastRelevance = relevance;
            }
            delete action;
        }
    }
    while (basket);
	
    if (!basket)
    {
        //sLog.outBasic("--- queue is empty ---");
        lastRelevance = 0.0f;
        PushDefaultActions();
        if (queue.Peek() && depth < 5)
            return DoNextAction(unit, depth + 1);
    }

    return actionExecuted;
}

ActionNode* Engine::createAction(const char* name)
{
    for (std::list<Strategy*>::iterator i = strategies.begin(); i != strategies.end(); i++)
    {
        Strategy* strategy = *i;
        ActionNode* node = strategy->createAction(name);
        if (node)
            return node;
    }
    ActionNode* node = actionFactory->createAction(name);
    if (!node)
    {
        ai->TellMaster("no one creates this action: ");
        ai->TellMaster(name);
    }
    return node;
}

BOOL Engine::MultiplyAndPush(NextAction** actions, float forceRelevance, BOOL skipPrerequisites)
{
    BOOL pushed = FALSE;
    if (actions)
    {
        for (int j=0; j<10; j++) // TODO: remove 10
        {
            NextAction* nextAction = actions[j];
            if (nextAction)
            {
                ActionNode* action = createAction(nextAction->getName());
                float k = nextAction->getRelevance();
                for (std::list<Multiplier*>::iterator i = multipliers.begin(); i!= multipliers.end(); i++)
                {
                    Multiplier* multiplier = *i;
                    k *= multiplier->GetValue(action->getAction());
                }

                if (forceRelevance > 0.0f)
                    k = forceRelevance;

                if (k > 0)
                {
                    queue.Push(new ActionBasket(action, k, skipPrerequisites));
                    pushed = TRUE;
                }

                delete nextAction;
            }
            else 
                break;
        }
        delete actions;
    }
    return pushed;
}

void Engine::ExecuteAction(const char* name)
{
    ActionNode *action = createAction(name);
    if (action)
    {
        if (actionExecutionListeners.ActionExecuted(action->getAction()))
            action->Execute();

        MultiplyAndPush(action->getContinuers());
        delete action;
    }
}

void Engine::addStrategy(const char* name)
{
    removeStrategy(name);
    strategies.push_back(actionFactory->createStrategy(name));
    
    Init();
}

void Engine::removeStrategy(const char* name)
{
    if (strategies.empty())
        return;

    for (std::list<Strategy*>::iterator i = strategies.begin(); i != strategies.end(); i++)
    {
        Strategy* strategy = *i;
        if (!strcmp(strategy->getName(), name))
        {
            strategies.remove(strategy);
            delete strategy;
            break;
        }
    }
}

void Engine::ProcessTriggers()
{
    for (std::list<TriggerNode*>::iterator i = triggers.begin(); i != triggers.end(); i++)
    {
        TriggerNode* trigger = *i;
        if (trigger->IsActive())
        {
            //sLog.outBasic("T:%s", trigger->getName());
            MultiplyAndPush(trigger->getHandlers());
        }
    }
}

void Engine::PushDefaultActions() 
{
    for (std::list<Strategy*>::iterator i = strategies.begin(); i != strategies.end(); i++)
    {
        Strategy* strategy = *i;
        MultiplyAndPush(strategy->getDefaultActions());
    }
}

string Engine::ListStrategies()
{
    string s = "Strategies: ";
    
    if (strategies.empty())
        return s;
    
    for (std::list<Strategy*>::iterator i = strategies.begin(); i != strategies.end(); i++)
    {
        Strategy* strategy = *i;
        s.append(strategy->getName());
        s.append(", ");
    }
    return s.substr(0, s.length() - 2);
}