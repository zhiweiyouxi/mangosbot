#include "pchdef.h"
#include "PriestTriggers.h"
#include "PriestMultipliers.h"
#include "HealPriestStrategy.h"
#include "PriestActions.h"

using namespace ai;

void HealPriestNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    CombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        new PowerWordFortitudeTrigger(ai), 
        NextAction::array(0, new NextAction("power word: fortitude", 60.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new PowerWordFortitudeOnPartyTrigger(ai), 
        NextAction::array(0, new NextAction("power word: fortitude on party", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new DivineSpiritTrigger(ai), 
        NextAction::array(0, new NextAction("divine spirit", 40.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new DivineSpiritOnPartyTrigger(ai), 
        NextAction::array(0, new NextAction("divine spirit on party", 30.0f), NULL)));


    triggers.push_back(new TriggerNode(
        new LowHealthTrigger(ai, 50),
        NextAction::array(0, new NextAction("power word: shield", 60.0f), new NextAction("heal", 60.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new PartyMemberLowHealthTrigger(ai, 50),
        NextAction::array(0, new NextAction("power word: shield on party", 50.0f), new NextAction("heal on party", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new NoAttackersTrigger(ai), 
        NextAction::array(0, new NextAction("attack least threat", 20.0f), NULL)));
}

void HealPriestNonCombatStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{
    CombatStrategy::InitMultipliers(multipliers);
}

ActionNode* HealPriestNonCombatStrategy::createAction(const char* name)
{
    ActionNode* node = CombatStrategy::createAction(name);
    if (node)
        return node;

    if (!strcmp("power word: fortitude", name)) 
    {
        return new ActionNode (new CastPowerWordFortitudeAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("power word: fortitude on party", name)) 
    {
        return new ActionNode (new CastPowerWordFortitudeOnPartyAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("divine spirit", name)) 
    {
        return new ActionNode (new CastDivineSpiritAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("divine spirit on party", name)) 
    {
        return new ActionNode (new CastDivineSpiritOnPartyAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    if (!strcmp("power word: shield", name)) 
    {
        return new ActionNode (new CastPowerWordShieldAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("renew", 50.0f), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("power word: shield on party", name)) 
    {
        return new ActionNode (new CastPowerWordShieldOnPartyAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("renew on party", 50.0f), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("renew", name)) 
    {
        return new ActionNode (new CastRenewAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("renew on party", name)) 
    {
        return new ActionNode (new CastRenewOnPartyAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("heal", name)) 
    {
        return new ActionNode (new CastHealAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("lesser heal"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("heal on party", name)) 
    {
        return new ActionNode (new CastHealOnPartyAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("lesser heal on party"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("lesser heal", name)) 
    {
        return new ActionNode (new CastLesserHealAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("lesser heal on party", name)) 
    {
        return new ActionNode (new CastLesserHealOnPartyAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("attack least threat", name)) 
    {
        return new ActionNode (new AttackLeastThreatAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else return NULL;
}



NextAction** HealPriestStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("shoot", 10.0f), NULL);
}

ActionNode* HealPriestStrategy::createAction(const char* name)
{
    ActionNode* node = HealPriestNonCombatStrategy::createAction(name);
    if (node)
        return node;

    if (!strcmp("shoot", name)) 
    {
        return new ActionNode (new CastShootAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else return NULL;
}

