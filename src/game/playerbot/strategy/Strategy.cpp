#include "../../pchdef.h"
#include "../playerbot.h"
#include "Strategy.h"
#include "GenericTriggers.h"

using namespace ai;

void CombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers) 
{
    triggers.push_back(new TriggerNode(
        new PanicTrigger(ai), 
        NextAction::array(0, new NextAction("healthstone", 100.0f), NULL)));

}

void MeleeCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers) 
{
    triggers.push_back(new TriggerNode(
        new EnemyOutOfMeleeTrigger(ai), 
        NextAction::array(0, new NextAction("reach melee", 10.0f), NULL)));
}

void RangedCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers) 
{
    triggers.push_back(new TriggerNode(
        new EnemyOutOfSpellRangeTrigger(ai), 
        NextAction::array(0, new NextAction("reach spell", 10.0f), NULL)));
}
