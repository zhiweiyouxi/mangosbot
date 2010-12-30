#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "MageTriggers.h"
#include "MageMultipliers.h"
#include "FireMageStrategy.h"
#include "MageActions.h"

using namespace ai;

NextAction** FireMageStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("fire blast", 1.0f), new NextAction("scorch", 1.0f), NULL);
}

void FireMageStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericMageStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        new FireballTrigger(ai), 
        NextAction::array(0, new NextAction("fireball", 5.0f), NULL)));
    triggers.push_back(new TriggerNode(
        new PyroblastTrigger(ai), 
        NextAction::array(0, new NextAction("pyroblast", 10.0f), NULL)));
    triggers.push_back(new TriggerNode(
        new BoostTrigger(ai, "combustion"),
        NextAction::array(0, new NextAction("combustion", 50.0f), NULL)));
}

void FireMageStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{
    GenericMageStrategy::InitMultipliers(multipliers);
}

ActionNode* FireMageStrategy::createAction(const char* name)
{
    ActionNode* node = GenericMageStrategy::createAction(name);
    if (node)
        return node;

    return NULL;
}