#include "pchdef.h"
#include "HunterActions.h"
#include "HunterActionFactory.h"
#include "DpsHunterStrategy.h"

using namespace ai;

Action* HunterActionFactory::createAction(const char* name)
{
    Action* action = ActionFactory::createAction(name);
    if (action)
        return action;

    CREATE_ACTION_RULE("auto shot", CastAutoShotAction);
    CREATE_ACTION_RULE("arcane shot", CastArcaneShotAction);
    CREATE_ACTION_RULE("concussive shot", CastConcussiveShotAction);
    CREATE_ACTION_RULE("distracting shot", CastDistractingShotAction);
    CREATE_ACTION_RULE("multi-shot", CastMultiShotAction);
    CREATE_ACTION_RULE("serpent sting", CastSerpentStingAction);
    CREATE_ACTION_RULE("scorpid sting", CastScorpidStingAction);
    CREATE_ACTION_RULE("aspect of the hawk", CastAspectOfTheHawkAction);
    CREATE_ACTION_RULE("hunter's mark", CastHuntersMarkAction);
    
    CREATE_ACTION_RULE("call pet", CastCallPetAction);
    CREATE_ACTION_RULE("mend pet", CastMendPetAction);
    CREATE_ACTION_RULE("revive pet", CastRevivePetAction);

    //CREATE_ACTION_RULE("", CastAction);

    return NULL;
}

Strategy* HunterActionFactory::createStrategy(const char* name)
{
    Strategy* strategy = ActionFactory::createStrategy(name);
    if (strategy)
        return strategy;

    if (!strcmp("dps hunter", name))
        return new DpsHunterStrategy(ai);


    return new GenericHunterStrategy(ai);
}
