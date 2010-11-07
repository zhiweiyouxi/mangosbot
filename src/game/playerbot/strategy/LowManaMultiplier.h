#pragma once
#include "Action.h"
#include "Multiplier.h"

namespace ai 
{
    class LowManaMultiplier : public Multiplier
    {
    public:
        LowManaMultiplier() : Multiplier() {}

    public:
        virtual float GetValue(Action* action);
    };

}