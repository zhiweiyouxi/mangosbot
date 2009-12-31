#include "pchdef.h"
#include "DruidTriggers.h"
#include "DruidMultipliers.h"
#include "BearTankDruidStrategy.h"

using namespace ai;

void BearTankDruidStrategy::InitTriggers(std::list<Trigger*> &triggers)
{
    GenericDruidStrategy::InitTriggers(triggers);
    
    triggers.push_back(new EnemyOutOfMeleeTrigger(ai));
    triggers.push_back(new BearTankDruidLoseAggroTrigger(ai));

    triggers.push_back(new MaulAvailable(ai));
    triggers.push_back(new SwipeAvailable(ai));
}

void BearTankDruidStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{

}
