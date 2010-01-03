#include "pchdef.h"
#include "ActionFactory.h"
#include "GenericActions.h"
#include "NonCombatActions.h"
#include "GenericNonCombatStrategy.h"

using namespace ai;

Action* ActionFactory::createAction(const char* name)
{
    if (!strcmp("flee", name))
        return new FleeAction(ai);

    if (!strcmp("melee", name))
        return new MeleeAction(ai);
    
    if (!strcmp("reach spell", name))
        return new ReachSpellAction(ai);

    if (!strcmp("lifeblood", name))
        return new CastLifeBloodAction(ai);

    if (!strcmp("healing potion", name))
        return new UseHealingPotion(ai);
    
    if (!strcmp("mana potion", name))
        return new UseManaPotion(ai);
    
    if (!strcmp("panic potion", name))
        return new UsePanicPotion(ai);
    
    if (!strcmp("eat", name))
        return new EatAction(ai);
    
    if (!strcmp("drink", name))
        return new DrinkAction(ai);

    if (!strcmp("follow", name))
        return new FollowAction(ai);

    if (!strcmp("stay", name))
        return new StayAction(ai);

    if (!strcmp("attack least threat", name))
        return new AttackLeastThreatAction(ai);
    

    return NULL;
}

Strategy* ActionFactory::createStrategy(const char* name)
{
    if (!strcmp("follow", name))
        return new FollowMasterNonCombatStrategy(ai);

    if (!strcmp("stay", name))
        return new StayNonCombatStrategy(ai);

    return NULL;
}