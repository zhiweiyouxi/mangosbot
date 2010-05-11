#include "pchdef.h"
#include "RacialsStrategy.h"
#include "HealthTriggers.h"

using namespace ai;

void RacialsStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
	triggers.push_back(new TriggerNode(
		new LowHealthTrigger(ai), 
		NextAction::array(0, new NextAction("lifeblood", 60.0f), NULL)));
}


ActionNode* RacialsStrategy::createAction(const char* name)
{
    return NULL;
}

