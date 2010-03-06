#include "pchdef.h"
#include "PriestTriggers.h"
#include "PriestMultipliers.h"
#include "DpsPriestStrategy.h"
#include "PriestActions.h"

using namespace ai;

NextAction** DpsPriestStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("mind blast", 10.0f), NULL);
}

void DpsPriestStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    HealPriestStrategy::InitTriggers(triggers);
    
    triggers.push_back(new TriggerNode(
        new DevouringPlagueTrigger(ai), 
        NextAction::array(0, new NextAction("devouring plague", 12.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new PowerWordPainTrigger(ai), 
        NextAction::array(0, new NextAction("shadow word: pain", 11.0f), NULL)));
}

void DpsPriestStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{
    HealPriestStrategy::InitMultipliers(multipliers);
}

ActionNode* DpsPriestStrategy::createAction(const char* name)
{
    ActionNode* node = HealPriestStrategy::createAction(name);
    if (node)
        return node;

    if (!strcmp("shadow word: pain", name)) 
    {
        return new ActionNode (new CastPowerWordPainAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("devouring plague", name)) 
    {
        return new ActionNode (new CastDevouringPlagueAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("mind blast", name)) 
    {
        return new ActionNode (new CastMindBlastAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("shoot"), NULL), 
            /*C*/ NextAction::array(0, new NextAction("shoot"), NULL));
    }
    else if (!strcmp("shoot", name)) 
    {
        return new ActionNode (new CastShootAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else return NULL;
}


void PriestBoostStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
}

