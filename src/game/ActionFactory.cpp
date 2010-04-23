#include "pchdef.h"
#include "ActionFactory.h"
#include "GenericActions.h"
#include "NonCombatActions.h"
#include "GenericNonCombatStrategy.h"

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
    else if (!strcmp("lifeblood", name)) 
    {
        return new ActionNode (new CastLifeBloodAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("gift of the naaru"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("gift of the naaru", name)) 
    {
        return new ActionNode (new CastGiftOfTheNaaruAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("healing potion"), NULL), 
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
    else if (!strcmp("attack bigger threat", name)) 
    {
        return new ActionNode (new AttackBiggerThreatAction(ai),  
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
    if (!strcmp("follow", name))
        return new FollowMasterNonCombatStrategy(ai);

    if (!strcmp("stay", name))
        return new StayNonCombatStrategy(ai);
    
    if (!strcmp("assist", name))
        return new AssistNonCombatStrategy(ai);

    if (!strcmp("tank nc", name))
        return new TankNonCombatStrategy(ai);

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