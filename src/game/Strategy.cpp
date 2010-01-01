#include "pchdef.h"
#include "Strategy.h"
#include "GenericTriggers.h"

using namespace ai;

void Strategy::InitTriggers(std::list<Trigger*> &triggers) 
{
    triggers.push_back(new PanicTrigger(ai));
}
