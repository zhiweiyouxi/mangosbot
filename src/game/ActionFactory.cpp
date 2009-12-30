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

    return NULL;
}

