#include "pchdef.h"
#include "PriestTriggers.h"
#include "PriestMultipliers.h"
#include "HealPriestStrategy.h"
#include "PriestActions.h"

using namespace ai;

void GenericPriestStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    CombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        new LowHealthTrigger(ai, 60, 40),
        NextAction::array(0, new NextAction("flash heal", 25.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new PartyMemberLowHealthTrigger(ai, 60, 40),
        NextAction::array(0, new NextAction("flash heal on party", 20.0f), NULL)));


    triggers.push_back(new TriggerNode(
        new LowHealthTrigger(ai, 40),
        NextAction::array(0, new NextAction("power word: shield", 60.0f), new NextAction("greater heal", 60.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new PartyMemberLowHealthTrigger(ai, 40),
        NextAction::array(0, new NextAction("power word: shield on party", 50.0f), new NextAction("greater heal on party", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new NeedCureTrigger(ai, "dispel magic", DISPEL_MAGIC),
        NextAction::array(0, new NextAction("dispel magic", 41.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new PartyMemberNeedCureTrigger(ai, "dispel magic", DISPEL_MAGIC),
        NextAction::array(0, new NextAction("dispel magic on party", 40.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new NeedCureTrigger(ai, "cure disease", DISPEL_DISEASE),
        NextAction::array(0, new NextAction("abolish disease", 31.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new PartyMemberNeedCureTrigger(ai, "cure disease", DISPEL_DISEASE),
        NextAction::array(0, new NextAction("abolish disease on party", 30.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new EnemyTooCloseTrigger(ai), 
        NextAction::array(0, new NextAction("fade", 50.0f), new NextAction("flee", 50.0f), NULL)));    

}

void GenericPriestStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{
    CombatStrategy::InitMultipliers(multipliers);
}

ActionNode* GenericPriestStrategy::createAction(const char* name)
{
    ActionNode* node = CombatStrategy::createAction(name);
    if (node)
        return node;

    if (!strcmp("inner fire", name)) 
    {
        return new ActionNode (new CastInnerFireAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
	else if (!strcmp("reach spell", name)) 
	{
		return new ActionNode (new ReachSpellAction(ai, 30.0f),  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
	else if (!strcmp("flee", name)) 
	{
		return new ActionNode (new FleeAction(ai, 30.0f),  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
    else if (!strcmp("shadowform", name)) 
    {
        return new ActionNode (new CastShadowformAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("remove shadowform", name)) 
    {
        return new ActionNode (new CastRemoveShadowformAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("holy nova", name)) 
    {
        return new ActionNode (new CastHolyNovaAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("power word: fortitude", name)) 
    {
        return new ActionNode (new CastPowerWordFortitudeAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("power word: fortitude on party", name)) 
    {
        return new ActionNode (new CastPowerWordFortitudeOnPartyAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("divine spirit", name)) 
    {
        return new ActionNode (new CastDivineSpiritAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("divine spirit on party", name)) 
    {
        return new ActionNode (new CastDivineSpiritOnPartyAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    if (!strcmp("power word: shield", name)) 
    {
        return new ActionNode (new CastPowerWordShieldAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NextAction::array(0, new NextAction("renew", 50.0f), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("power word: shield on party", name)) 
    {
        return new ActionNode (new CastPowerWordShieldOnPartyAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NextAction::array(0, new NextAction("renew on party", 50.0f), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("renew", name)) 
    {
        return new ActionNode (new CastRenewAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("renew on party", name)) 
    {
        return new ActionNode (new CastRenewOnPartyAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("greater heal", name)) 
    {
        return new ActionNode (new CastGreaterHealAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NextAction::array(0, new NextAction("heal"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("greater heal on party", name)) 
    {
        return new ActionNode (new CastGreaterHealOnPartyAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NextAction::array(0, new NextAction("heal on party"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("heal", name)) 
    {
        return new ActionNode (new CastHealAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NextAction::array(0, new NextAction("lesser heal"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("heal on party", name)) 
    {
        return new ActionNode (new CastHealOnPartyAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NextAction::array(0, new NextAction("lesser heal on party"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("lesser heal", name)) 
    {
        return new ActionNode (new CastLesserHealAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("lesser heal on party", name)) 
    {
        return new ActionNode (new CastLesserHealOnPartyAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("flash heal", name)) 
    {
        return new ActionNode (new CastFlashHealAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("flash heal on party", name)) 
    {
        return new ActionNode (new CastFlashHealOnPartyAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("dispel magic", name)) 
    {
        return new ActionNode (new CastDispelMagicAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("dispel magic on party", name)) 
    {
        return new ActionNode (new CastDispelMagicOnPartyAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("dispel magic on target", name)) 
    {
        return new ActionNode (new CastDispelMagicOnTargetAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("cure disease", name)) 
    {
        return new ActionNode (new CastCureDiseaseAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("cure disease on party", name)) 
    {
        return new ActionNode (new CastCureDiseaseOnPartyAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("abolish disease", name)) 
    {
        return new ActionNode (new CastAbolishDiseaseAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("abolish disease on party", name)) 
    {
        return new ActionNode (new CastAbolishDiseaseOnPartyAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("fade", name)) 
    {
        return new ActionNode (new CastFadeAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else return NULL;
}



