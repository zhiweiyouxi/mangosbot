#include "pchdef.h"
#include "HunterTriggers.h"
#include "HunterMultipliers.h"
#include "DpsHunterStrategy.h"
#include "HunterActions.h"

using namespace ai;

void DpsHunterStrategy::InitTriggers(std::list<Trigger*> &triggers)
{
    GenericHunterStrategy::InitTriggers(triggers);

    triggers.push_back(new HunterNoStingsActiveTrigger(ai));
    triggers.push_back(new NoAttackersTrigger(ai));

    triggers.push_back(new HunterHasNoPetTrigger(ai));
    triggers.push_back(new HuntersPetDeadTrigger(ai));
    triggers.push_back(new HuntersPetLowHealthTrigger(ai));
}

void DpsHunterStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{
    GenericHunterStrategy::InitMultipliers(multipliers);
}

ActionNode* DpsHunterStrategy::createAction(const char* name)
{
    ActionNode* node = GenericHunterStrategy::createAction(name);
    if (node)
        return node;

    if (!strcmp("auto shot", name)) 
    {
        return new ActionNode (new CastAutoShotAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("arcane shot", 11.0f), new NextAction("auto shot", 10.0f), NULL));
    }
    else if (!strcmp("arcane shot", name)) 
    {
        return new ActionNode (new CastArcaneShotAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("arcane shot", 11.0f), new NextAction("auto shot", 10.0f), NULL));
    }
    else if (!strcmp("concussive shot", name)) 
    {
        return new ActionNode (new CastConcussiveShotAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("arcane shot", 11.0f), new NextAction("auto shot", 10.0f), NULL));
    }
    else if (!strcmp("distracting shot", name)) 
    {
        return new ActionNode (new CastDistractingShotAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("arcane shot", 11.0f), new NextAction("auto shot", 10.0f), NULL));
    }
    else if (!strcmp("multi-shot", name)) 
    {
        return new ActionNode (new CastMultiShotAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("arcane shot", 11.0f), new NextAction("auto shot", 10.0f), NULL));
    }
    else if (!strcmp("serpent sting", name)) 
    {
        return new ActionNode (new CastSerpentStingAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("arcane shot", 11.0f), new NextAction("auto shot", 10.0f), NULL));
    }
    else if (!strcmp("scorpid sting", name)) 
    {
        return new ActionNode (new CastScorpidStingAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("arcane shot", 11.0f), new NextAction("auto shot", 10.0f), NULL));
    }
    else if (!strcmp("hunter's mark", name)) 
    {
        return new ActionNode (new CastHuntersMarkAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("arcane shot", 11.0f), new NextAction("auto shot", 10.0f), NULL));
    }
    else if (!strcmp("mend pet", name)) 
    {
        return new ActionNode (new CastMendPetAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("revive pet", name)) 
    {
        return new ActionNode (new CastRevivePetAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else return NULL;
}