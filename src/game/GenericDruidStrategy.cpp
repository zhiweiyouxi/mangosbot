#include "pchdef.h"
#include "DruidTriggers.h"
#include "GenericDruidStrategy.h"

using namespace ai;

void GenericDruidStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    CombatStrategy::InitTriggers(triggers);
    
    triggers.push_back(new TriggerNode(
        new DruidLowHealthTrigger(ai),
        NextAction::array(0, new NextAction("lifeblood", 60.0f), new NextAction("rejuvenation", 50.0f), NULL)));
}
