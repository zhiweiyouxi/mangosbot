#include "pchdef.h"
#include "Strategy.h"
#include "GenericTriggers.h"

using namespace ai;

void CombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers) 
{
    triggers.push_back(new TriggerNode(
        new PanicTrigger(ai), 
        NextAction::array(0, new NextAction("healthstone", 100.0f), NULL)));

}
