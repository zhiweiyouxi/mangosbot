#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PaladinTriggers.h"
#include "PaladinMultipliers.h"
#include "PaladinBuffStrategies.h"
#include "PaladinActions.h"

using namespace ai;

void PaladinBuffManaStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        new SealTrigger(ai), 
        NextAction::array(0, new NextAction("seal of wisdom", 24.0f), NULL)));
}

void PaladinBuffHealthStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        new SealTrigger(ai), 
        NextAction::array(0, new NextAction("seal of light", 24.0f), NULL)));
}

void PaladinBuffDpsStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        new SealTrigger(ai), 
        NextAction::array(0, new NextAction("seal of command", 24.0f), NULL)));
}
