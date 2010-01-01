#include "pchdef.h"
#include "DruidActions.h"
#include "DruidActionFactory.h"
#include "BearTankDruidStrategy.h"

using namespace ai;

Action* DruidActionFactory::createAction(const char* name)
{
    CREATE_ACTION_RULE("melee", DruidMeleeAction);
    
    Action* action = ActionFactory::createAction(name);
    if (action)
        return action;

    CREATE_ACTION_RULE("faerie fire", CastFaerieFireAction);
    
    CREATE_ACTION_RULE("caster form", CastCasterFormAction);
    CREATE_ACTION_RULE("bear form", CastBearFormAction);
    CREATE_ACTION_RULE("dire bear form", CastDireBearFormAction);
    
    CREATE_ACTION_RULE("maul", CastMaulAction);
    CREATE_ACTION_RULE("swipe", CastSwipeAction);
    
    CREATE_ACTION_RULE("regrowth", CastRegrowthAction);
    CREATE_ACTION_RULE("rejuvenation", CastRejuvenationAction);

    CREATE_ACTION_RULE("regrowth on party", CastRegrowthOnPartyAction);
    CREATE_ACTION_RULE("rejuvenation on party", CastRejuvenationOnPartyAction);

    CREATE_ACTION_RULE("growl", CastGrowlAction);
    CREATE_ACTION_RULE("demoralizing roar", CastDemoralizingRoarAction);
        

    return NULL;
}


Strategy* DruidActionFactory::createStrategy(const char* name)
{
    Strategy* strategy = ActionFactory::createStrategy(name);
    if (strategy)
        return strategy;

    if (!strcmp("bear tank", name))
        return new BearTankDruidStrategy(ai);

    return new GenericDruidStrategy(ai);
}
