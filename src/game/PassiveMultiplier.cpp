#include "pchdef.h"
#include "PassiveMultiplier.h"

using namespace ai;

float PassiveMultiplier::GetValue(Action* action)
{
    if (action == NULL) return 1.0f;

    else if (!strcmp("attack least threat", action->getName()))
        return 0;

    else if (!strcmp("attack bigger threat", action->getName()))
        return 0;

    else if (!strcmp("reach melee", action->getName()))
        return 0;

    else if (!strcmp("reach spell", action->getName()))
        return 0;

    return 1.0f;
}