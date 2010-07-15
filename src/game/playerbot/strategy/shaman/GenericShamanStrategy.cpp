#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "ShamanTriggers.h"
#include "ShamanMultipliers.h"
#include "HealShamanStrategy.h"
#include "ShamanActions.h"

using namespace ai;

void GenericShamanStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    CombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        new WaterShieldTrigger(ai), 
        NextAction::array(0, new NextAction("water shield", 22.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new WindfuryTotemTrigger(ai), 
        NextAction::array(0, new NextAction("windfury totem", 18.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new ManaSpringTotemTrigger(ai), 
        NextAction::array(0, new NextAction("mana spring totem", 16.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new FlametongueTotemTrigger(ai), 
        NextAction::array(0, new NextAction("flametongue totem", 17.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new StrengthOfEarthTotemTrigger(ai), 
        NextAction::array(0, new NextAction("strength of earth totem", 19.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new InterruptSpellTrigger(ai, "wind shear"), 
        NextAction::array(0, new NextAction("wind shear", 15.0f), NULL)));
}

void GenericShamanStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{
    CombatStrategy::InitMultipliers(multipliers);
}

ActionNode* GenericShamanStrategy::createAction(const char* name)
{
    ActionNode* node = CombatStrategy::createAction(name);
    if (node)
        return node;

    if (!strcmp("water shield", name)) 
    {
        return new ActionNode (new CastWaterShieldAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
	else if (!strcmp("reach spell", name)) 
	{
		return new ActionNode (new ReachSpellAction(ai),  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
	else if (!strcmp("flee", name)) 
	{
		return new ActionNode (new FleeAction(ai),  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
    else if (!strcmp("strength of earth totem", name)) 
    {
        return new ActionNode (new CastStrengthOfEarthTotemAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("flametongue totem", name)) 
    {
        return new ActionNode (new CastFlametongueTotemAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("windfury totem", name)) 
    {
        return new ActionNode (new CastWindfuryTotemAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("mana spring totem", name)) 
    {
        return new ActionNode (new CastManaSpringTotemAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("wind shear", name)) 
    {
        return new ActionNode (new CastWindShearAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("earthliving weapon", name)) 
    {
        return new ActionNode (new CastEarthlivingWeaponAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("flametongue weapon"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("rockbiter weapon", name)) 
    {
        return new ActionNode (new CastRockbiterWeaponAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("flametongue weapon", name)) 
    {
        return new ActionNode (new CastFlametongueWeaponAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("frostbrand weapon"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("frostbrand weapon", name)) 
    {
        return new ActionNode (new CastFrostbrandWeaponAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("rockbiter weapon"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("windfury weapon", name)) 
    {
        return new ActionNode (new CastWindfuryWeaponAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("rockbiter weapon"), NULL), 
            /*C*/ NULL);
    }
    return NULL;
}



