#include "pchdef.h"
#include "MageActionFactory.h"
#include "MageActions.h"

using namespace ai;

Action* MageActionFactory::createAction(const char* name)
{
    Action* action = ActionFactory::createAction(name);
    if (action)
        return action;

    CREATE_ACTION_RULE("frostbolt", CastFrostBoltAction);
    CREATE_ACTION_RULE("frost nova", CastFrostNovaAction);
    CREATE_ACTION_RULE("ice lance", CastIceLanceAction);
    CREATE_ACTION_RULE("fireball", CastFireBallAction);
    CREATE_ACTION_RULE("fire blast", CastFireBlastAction);
    CREATE_ACTION_RULE("pyroblast", CastPyroblastAction);
    CREATE_ACTION_RULE("scorch", CastScorchAction);
    CREATE_ACTION_RULE("blast wave", CastBlastWaveAction);
    CREATE_ACTION_RULE("arcane explosion", CastArcaneExplosionAction);
    CREATE_ACTION_RULE("arcane blast", CastArcaneBlastAction);
    CREATE_ACTION_RULE("counterspell", CastCounterspellAction);
 
    throw new std::exception(name);
    return NULL;
}