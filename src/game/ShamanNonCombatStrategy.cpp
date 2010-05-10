#include "pchdef.h"
#include "ShamanTriggers.h"
#include "ShamanMultipliers.h"
#include "ShamanNonCombatStrategy.h"
#include "ShamanActions.h"

using namespace ai;

void ShamanNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    CombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        new WaterShieldTrigger(ai), 
        NextAction::array(0, new NextAction("water shield", 21.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new EarthlivingWeaponTrigger(ai), 
        NextAction::array(0, new NextAction("earthliving weapon", 22.0f), NULL)));

}

void ShamanNonCombatStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{
    CombatStrategy::InitMultipliers(multipliers);
}

ActionNode* ShamanNonCombatStrategy::createAction(const char* name)
{
    ActionNode* node = CombatStrategy::createAction(name);
    if (node)
        return node;

    if (!strcmp("earthliving weapon", name)) 
    {
        return new ActionNode (new CastEarthlivingWeaponAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("water shield", name)) 
    {
        return new ActionNode (new CastWaterShieldAction(ai),  
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
    else return NULL;
}



