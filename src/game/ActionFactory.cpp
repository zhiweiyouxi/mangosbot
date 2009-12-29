#include "pchdef.h"
#include "ActionFactory.h"
#include "GenericActions.h"

using namespace ai;

Action* ActionFactory::createAction(const char* name)
{
    if (!strcmp("flee", name))
        return new FleeAction(ai);

    return NULL;
}