#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PriestTriggers.h"
#include "PriestMultipliers.h"
#include "HealPriestStrategy.h"
#include "PriestActions.h"

using namespace ai;

NextAction** HealPriestStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("shoot", 10.0f), NULL);
}

void HealPriestStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericPriestStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
                       new MyAttackerCountTrigger(ai, 2),
                       NextAction::array(0, new NextAction("fade", 90.0f), NULL)));
}

ActionNode* HealPriestStrategy::createAction(const char* name)
{
    ActionNode* node = GenericPriestStrategy::createAction(name);
    if (node)
        return node;

    else return NULL;
}

