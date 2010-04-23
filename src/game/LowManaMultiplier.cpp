#include "pchdef.h"
#include "LowManaMultiplier.h"
#include <math.h>

using namespace ai;

float LowManaMultiplier::GetValue(Action* action)
{
    if (action == NULL) return 1.0f;

    // Hunter
    if (!strcmp("arcane shot", action->getName()) || 
        !strcmp("multi-shot", action->getName()) ||
        !strcmp("serpent sting", action->getName()) ||
        !strcmp("viper sting", action->getName()) ||
        !strcmp("scorpid sting", action->getName()) 
        ) return !(rand() % 50) ? 1 : 0;

    // Priest
    if (!strcmp("shadow word: pain", action->getName()) || 
        !strcmp("devouring plague", action->getName()) || 
        !strcmp("mind blast", action->getName()) 
        ) return !(rand() % 50) ? 1 : 0;


    return 1.0f;
}