#include "pchdef.h"
#include "HunterTriggers.h"
#include "HunterMultipliers.h"
#include "DpsHunterStrategy.h"
#include "HunterActions.h"

using namespace ai;

NextAction** DpsHunterStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("hunter's mark", 50.0f), NULL);
}

void DpsHunterStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericHunterStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        new HunterAspectOfTheViperTrigger(ai), 
        NextAction::array(0, new NextAction("aspect of the viper", 91.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new HunterAspectOfTheHawkTrigger(ai), 
        NextAction::array(0, new NextAction("aspect of the hawk", 90.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new HunterNoStingsActiveTrigger(ai), 
        NextAction::array(0, new NextAction("serpent sting", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new LowManaTrigger(ai), 
        NextAction::array(0, new NextAction("viper sting", 51.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new NoAttackersTrigger(ai), 
        NextAction::array(0, new NextAction("attack least threat", 9.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new NoPetTrigger(ai), 
        NextAction::array(0, new NextAction("call pet", 60.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new HuntersPetDeadTrigger(ai), 
        NextAction::array(0, new NextAction("revive pet", 60.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new HuntersPetLowHealthTrigger(ai), 
        NextAction::array(0, new NextAction("mend pet", 60.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new NoAttackersTrigger(ai), 
        NextAction::array(0, new NextAction("attack least threat", 9.0f), NULL)));
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
            /*C*/ NextAction::array(0, new NextAction("aimed shot", 11.0f), new NextAction("auto shot", 10.0f), NULL));
    }
    else if (!strcmp("aimed shot", name)) 
    {
        return new ActionNode (new CastAimedShotAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("arcane shot", 10.0f), NULL), 
            /*C*/ NextAction::array(0, new NextAction("auto shot", 10.0f), NULL));
    }
    else if (!strcmp("arcane shot", name)) 
    {
        return new ActionNode (new CastArcaneShotAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("auto shot", 10.0f), NULL));
    }
    else if (!strcmp("concussive shot", name)) 
    {
        return new ActionNode (new CastConcussiveShotAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("aimed shot", 11.0f), new NextAction("auto shot", 10.0f), NULL));
    }
    else if (!strcmp("distracting shot", name)) 
    {
        return new ActionNode (new CastDistractingShotAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("aimed shot", 11.0f), new NextAction("auto shot", 10.0f), NULL));
    }
    else if (!strcmp("multi-shot", name)) 
    {
        return new ActionNode (new CastMultiShotAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("aimed shot", 11.0f), new NextAction("auto shot", 10.0f), NULL));
    }
    else if (!strcmp("serpent sting", name)) 
    {
        return new ActionNode (new CastSerpentStingAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("aimed shot", 11.0f), new NextAction("auto shot", 10.0f), NULL));
    }
    else if (!strcmp("viper sting", name)) 
    {
        return new ActionNode (new CastViperStingAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("aimed shot", 11.0f), new NextAction("auto shot", 10.0f), NULL));
    }
    else if (!strcmp("scorpid sting", name)) 
    {
        return new ActionNode (new CastScorpidStingAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("aimed shot", 11.0f), new NextAction("auto shot", 10.0f), NULL));
    }
    else if (!strcmp("hunter's mark", name)) 
    {
        return new ActionNode (new CastHuntersMarkAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("aimed shot", 11.0f), new NextAction("auto shot", 10.0f), NULL));
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