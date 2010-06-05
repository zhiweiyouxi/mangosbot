#include "../../pchdef.h"
#include "../playerbot.h"
#include "ActionFactory.h"
#include "GenericActions.h"
#include "NonCombatActions.h"
#include "GenericNonCombatStrategy.h"
#include "RacialsStrategy.h"

using namespace ai;

ActionNode* ActionFactory::createAction(const char* name)
{
    if (!strcmp("flee", name)) 
    {
        return new ActionNode (new FleeAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("melee", name)) 
    {
        return new ActionNode (new MeleeAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("reach melee"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("reach melee", name)) 
    {
        return new ActionNode (new ReachMeleeAction(ai),  
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
	else if (!strcmp("healthstone", name)) 
	{
		return new ActionNode (new UseHealthstone(ai),  
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("panic potion"), NULL), 
			/*C*/ NULL);
	}
    else if (!strcmp("panic potion", name)) 
    {
        return new ActionNode (new UsePanicPotion(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("healing potion"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("healing potion", name)) 
    {
        return new ActionNode (new UseHealingPotion(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("mana potion"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("mana potion", name)) 
    {
        return new ActionNode (new UseManaPotion(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("flee"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("eat", name)) 
    {
        return new ActionNode (new EatAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("drink", name)) 
    {
        return new ActionNode (new DrinkAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("tank assist", name)) 
    {
        return new ActionNode (new TankAssistAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("dps assist", name)) 
    {
        return new ActionNode (new DpsAssistAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("loot", name)) 
    {
        return new ActionNode (new LootAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else return NULL;
}

Strategy* ActionFactory::createStrategy(const char* name)
{
	if (!strcmp("racials", name))
		return new RacialsStrategy(ai);

    if (!strcmp("follow", name))
        return new FollowMasterNonCombatStrategy(ai);

    if (!strcmp("stay", name))
        return new StayNonCombatStrategy(ai);
    
    if (!strcmp("dps assist", name))
        return new DpsAssistStrategy(ai);

	if (!strcmp("dps aoe", name))
		return new DpsAoeStrategy(ai);

    if (!strcmp("tank assist", name))
        return new TankAssistStrategy(ai);

	if (!strcmp("tank aoe", name))
		return new TankAoeStrategy(ai);

    if (!strcmp("loot", name))
        return new LootNonCombatStrategy(ai);
    
    if (!strcmp("goaway", name))
        return new GoAwayNonCombatStrategy(ai);
    
    if (!strcmp("emote", name))
        return new RandomEmoteStrategy(ai);

    if (!strcmp("passive", name))
        return new PassiveStrategy(ai);
    
    if (!strcmp("low mana", name))
        return new LowManaStrategy(ai);

    if (!strcmp("food", name))
        return new UseFoodStrategy(ai);

    return NULL;
}