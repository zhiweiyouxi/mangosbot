#include "pchdef.h"
#include "MageMultipliers.h"
#include "MageActions.h"

using namespace ai;

float FrostMageMultiplier::GetValue(Action* action)
{
    if (action)
    {
        if (action->getKind() == ACTION_KIND_FROST)
            return 2.0f;
    }
    return 1.0f;
}