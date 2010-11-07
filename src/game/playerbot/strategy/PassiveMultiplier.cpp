#include "../../pchdef.h"
#include "../playerbot.h"
#include "PassiveMultiplier.h"

using namespace ai;

float PassiveMultiplier::GetValue(Action* action) {
    if (!action) 
		return 1.0f;

    const char* name = action->getName();

    if (!strcmp("follow", name) ||
        !strcmp("stay", name))
        return 1.0f;

    return 0;
}