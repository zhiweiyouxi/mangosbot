#include "pchdef.h"
#include "GenericTriggers.h"
#include "GenericNonCombatStrategy.h"
#include "GenericActions.h"
#include "NonCombatActions.h"
#include "PassiveMultiplier.h"
#include "LowManaMultiplier.h"

using namespace ai;

void UseFoodStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    Strategy::InitTriggers(triggers);
    
    triggers.push_back(new TriggerNode(
        new LowHealthTrigger(ai), 
        NextAction::array(0, new NextAction("eat", 9.0f), NULL)));
    
    triggers.push_back(new TriggerNode(
        new LowManaTrigger(ai), 
        NextAction::array(0, new NextAction("drink", 9.0f), NULL)));
}

void LootNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        new LootAvailableTrigger(ai), 
        NextAction::array(0, new NextAction("loot", 2.0f), NULL)));
}


void TankAssistStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        new NoAttackersTrigger(ai), 
        NextAction::array(0, new NextAction("attack bigger threat", 50.0f), NULL)));
}

void DpsAssistStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        new NoAttackersTrigger(ai), 
        NextAction::array(0, new NextAction("attack least threat", 50.0f), NULL)));
}

NextAction** StayNonCombatStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("stay", 1.0f), NULL);
}

ActionNode* StayNonCombatStrategy::createAction(const char* name)
{
    if (!strcmp("stay", name)) 
    {
        return new ActionNode (new StayAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else return NULL;
}

NextAction** FollowMasterNonCombatStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("follow", 1.0f), NULL);
}

ActionNode* FollowMasterNonCombatStrategy::createAction(const char* name)
{
    if (!strcmp("follow", name)) 
    {
        return new ActionNode (new FollowAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else return NULL;
}


NextAction** GoAwayNonCombatStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("goaway", 1.0f), NULL);
}

ActionNode* GoAwayNonCombatStrategy::createAction(const char* name)
{
    if (!strcmp("goaway", name)) 
    {
        return new ActionNode (new GoAwayAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else return NULL;
}



void RandomEmoteStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        new RandomTrigger(ai, 20), 
        NextAction::array(0, new NextAction("emote", 1.0f), NULL)));
}

ActionNode* RandomEmoteStrategy::createAction(const char* name)
{
    if (!strcmp("emote", name)) 
    {
        return new ActionNode (new EmoteAction(ai, 0),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else return NULL;
}

void PassiveStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{
    multipliers.push_back(new PassiveMultiplier());
}

void LowManaStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{
    multipliers.push_back(new LowManaMultiplier());
}
