#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PaladinTriggers.h"
#include "PaladinMultipliers.h"
#include "DpsPaladinStrategy.h"
#include "PaladinActions.h"

using namespace ai;

NextAction** DpsPaladinStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("melee", 10.0f), NULL);
}

void DpsPaladinStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericPaladinStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        new DevotionAuraTrigger(ai), 
        NextAction::array(0, new NextAction("retribution aura", 25.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new JudgementOfLightTrigger(ai), 
        NextAction::array(0, new NextAction("judgement of wisdom", 1.2f), NULL)));

    triggers.push_back(new TriggerNode(
        new SealTrigger(ai), 
        NextAction::array(0, new NextAction("seal of command", 24.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new BlessingTrigger(ai), 
        NextAction::array(0, new NextAction("blessing of might", 21.0f), NULL)));
}

void DpsPaladinStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{

}

ActionNode* DpsPaladinStrategy::createAction(const char* name)
{
    if (!strcmp("retribution aura", name)) 
    {
        return new ActionNode (new CastRetributionAuraAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("seal of command", name)) 
    {
        return new ActionNode (new CastSealOfCommandAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("seal of wisdom"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("judgement of wisdom", name)) 
    {
        return new ActionNode (new CastJudgementOfWisdomAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("judgement of light"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("blessing of might", name)) 
    {
        return new ActionNode (new CastBlessingOfMightAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("blessing of kings"), NULL), 
            /*C*/ NULL);
    }

    else return GenericPaladinStrategy::createAction(name);
}