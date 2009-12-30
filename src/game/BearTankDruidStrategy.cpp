#include "pchdef.h"
#include "DruidTriggers.h"
#include "DruidMultipliers.h"
#include "BearTankDruidStrategy.h"

using namespace ai;

void BearTankDruidStrategy::InitTriggers(std::list<Trigger*> &triggers)
{
    triggers.push_back(new EnemyOutOfMeleeTrigger(ai));
}

void BearTankDruidStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{

}
