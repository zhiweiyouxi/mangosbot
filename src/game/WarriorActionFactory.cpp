#include "pchdef.h"
#include "WarriorActions.h"
#include "WarriorActionFactory.h"
#include "GenericWarriorNonCombatStrategy.h"
#include "TankWarriorStrategy.h"

using namespace ai;

Action* WarriorActionFactory::createAction(const char* name)
{
    Action* action = ActionFactory::createAction(name);
    if (action)
        return action;

    CREATE_ACTION_RULE("rend", CastRendAction);
    CREATE_ACTION_RULE("heroic strike", CastHeroicStrikeAction);
    CREATE_ACTION_RULE("mocking blow", CastMockingBlowAction);
    CREATE_ACTION_RULE("taunt", CastTauntAction);
    CREATE_ACTION_RULE("revenge", CastRevengeAction);
    CREATE_ACTION_RULE("disarm", CastDisarmAction);
    CREATE_ACTION_RULE("sunder armor", CastSunderArmorAction);
    CREATE_ACTION_RULE("demoralizing shout", CastDemoralizingShoutAction);
    CREATE_ACTION_RULE("shield bash", CastShieldBashAction);
    CREATE_ACTION_RULE("intimidating shout", CastIntimidatingShoutAction);
    CREATE_ACTION_RULE("battle shout", CastBattleShoutAction);
    CREATE_ACTION_RULE("thunder clap", CastThunderClapAction);
    CREATE_ACTION_RULE("defensive stance", CastDefensiveStanceAction);

    return NULL;
}


Strategy* WarriorActionFactory::createStrategy(const char* name)
{
    Strategy* strategy = ActionFactory::createStrategy(name);
    if (strategy)
        return strategy;

    if (!strcmp("tank", name))
        return new TankWarriorStrategy(ai);

    if (!strcmp("warrior non combat", name))
        return new GenericWarriorNonCombatStrategy(ai);

    return new GenericWarriorStrategy(ai);
}
