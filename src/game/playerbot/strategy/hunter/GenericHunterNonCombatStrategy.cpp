#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "HunterTriggers.h"
#include "HunterMultipliers.h"
#include "GenericHunterNonCombatStrategy.h"
#include "HunterActions.h"

using namespace ai;

void HunterBuffSpeedNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericNonCombatStrategy::InitTriggers(triggers);
    
    triggers.push_back(new TriggerNode(
        new HunterAspectOfThePackTrigger(ai), 
        NextAction::array(0, new NextAction("aspect of the pack", 1.0f), NULL)));
}

void GenericHunterNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericNonCombatStrategy::InitTriggers(triggers);
    
    triggers.push_back(new TriggerNode(
        new AttackerCountTrigger(ai, 1), 
        NextAction::array(0, new NextAction("aspect of the hawk", 90.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new NoPetTrigger(ai), 
        NextAction::array(0, new NextAction("call pet", 60.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new HuntersPetDeadTrigger(ai), 
        NextAction::array(0, new NextAction("revive pet", 60.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new HuntersPetLowHealthTrigger(ai), 
        NextAction::array(0, new NextAction("mend pet", 60.0f), NULL)));
}


ActionNode* GenericHunterNonCombatStrategy::createAction(const char* name)
{
	return NULL;
}