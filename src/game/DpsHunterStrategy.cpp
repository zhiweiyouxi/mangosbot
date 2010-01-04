#include "pchdef.h"
#include "HunterTriggers.h"
#include "HunterMultipliers.h"
#include "DpsHunterStrategy.h"

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
