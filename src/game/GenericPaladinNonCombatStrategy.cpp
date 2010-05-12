#include "pchdef.h"
#include "PaladinTriggers.h"
#include "PaladinMultipliers.h"
#include "GenericPaladinNonCombatStrategy.h"
#include "PaladinActions.h"

using namespace ai;

void GenericPaladinNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericNonCombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        new BlessingTrigger(ai), 
        NextAction::array(0, new NextAction("blessing of sanctuary", 21.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new BlessingOfKingsOnPartyTrigger(ai), 
        NextAction::array(0, new NextAction("blessing of kings on party", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new DevotionAuraTrigger(ai), 
        NextAction::array(0, new NextAction("devotion aura", 25.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new SealTrigger(ai), 
        NextAction::array(0, new NextAction("seal of light", 24.0f), NULL)));

	triggers.push_back(new TriggerNode(
		new PartyMemberDeadTrigger(ai),
		NextAction::array(0, new NextAction("redemption", 30.0f), NULL)));
}

ActionNode* GenericPaladinNonCombatStrategy::createAction(const char* name)
{
    if (!strcmp("devotion aura", name)) 
    {
        return new ActionNode (new CastDevotionAuraAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
	else if (!strcmp("seal of light", name)) 
	{
		return new ActionNode (new CastSealOfLightAction(ai),  
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("seal of justice"), NULL), 
			/*C*/ NULL);
	}
    else if (!strcmp("seal of justice", name)) 
    {
        return new ActionNode (new CastSealOfJusticeAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("seal of righteousness"), NULL), 
            /*C*/ NULL);
    }
	else if (!strcmp("seal of righteousness", name)) 
	{
		return new ActionNode (new CastSealOfRighteousnessAction(ai),  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
    else if (!strcmp("blessing of sanctuary", name)) 
    {
        return new ActionNode (new CastBlessingOfSanctuaryAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("blessing of kings", name)) 
    {
        return new ActionNode (new CastBlessingOfKingsAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("blessing of kings on party", name)) 
    {
        return new ActionNode (new CastBlessingOfKingsOnPartyAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
	else if (!strcmp("redemption", name)) 
	{
		return new ActionNode (new CastRedemptionAction(ai),  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
    else return NULL;
}
