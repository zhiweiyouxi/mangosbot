#include "pchdef.h"
#include "DruidTriggers.h"
#include "DruidMultipliers.h"
#include "CatDpsDruidStrategy.h"

using namespace ai;

void CatDpsDruidStrategy::InitTriggers(std::list<Trigger*> &triggers)
{
    GenericDruidStrategy::InitTriggers(triggers);
    triggers.push_back(new EnemyOutOfMeleeTrigger(ai));
}

void CatDpsDruidStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{

}
