#include "pchdef.h"
#include "MageMultipliers.h"
#include "FrostMageStrategy.h"

using namespace ai;

void FrostMageStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{
    multipliers.push_back(new FrostMageMultiplier());
}