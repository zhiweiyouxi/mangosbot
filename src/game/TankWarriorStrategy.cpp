#include "pchdef.h"
#include "WarriorTriggers.h"
#include "WarriorMultipliers.h"
#include "TankWarriorStrategy.h"

using namespace ai;

void TankWarriorStrategy::InitTriggers(std::list<Trigger*> &triggers)
{
    GenericWarriorStrategy::InitTriggers(triggers);
    
    triggers.push_back(new DefensiveStanceTrigger(ai));
    triggers.push_back(new EnemyOutOfMeleeTrigger(ai));
    triggers.push_back(new WarriorLoseAggroTrigger(ai));

    triggers.push_back(new HeroicStrikeAvailable(ai));
    triggers.push_back(new WarriorDemoralizeAttackers(ai));

    triggers.push_back(new TankNoAttackersTrigger(ai));
}

void TankWarriorStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{

}
