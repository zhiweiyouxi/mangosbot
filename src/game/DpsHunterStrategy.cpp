#include "pchdef.h"
#include "HunterTriggers.h"
#include "HunterMultipliers.h"
#include "DpsHunterStrategy.h"

using namespace ai;

void DpsHunterStrategy::InitTriggers(std::list<Trigger*> &triggers)
{
    GenericHunterStrategy::InitTriggers(triggers);    
}

void DpsHunterStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{
    GenericHunterStrategy::InitMultipliers(multipliers);
}
