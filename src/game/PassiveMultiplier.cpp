#include "pchdef.h"
#include "PassiveMultiplier.h"

using namespace ai;

float PassiveMultiplier::GetValue(Action* action)
{
    if (action == NULL) return 1.0f;

    const char* name = action->getName();
    if (!strcmp("attack least threat", name) ||
        !strcmp("attack bigger threat", name) ||
        !strcmp("reach melee", name) ||
        !strcmp("melee", name) ||
        !strcmp("reach spell", name))
        return 0;

    return 1.0f;
}