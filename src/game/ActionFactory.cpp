#include "pchdef.h"
#include "ActionFactory.h"
#include "GenericActions.h"

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

    return NULL;
}

