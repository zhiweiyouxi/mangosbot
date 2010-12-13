#pragma once
#include "Action.h"
#include "Multiplier.h"

namespace ai 
{
    class PassiveMultiplier : public Multiplier
    {
    public:
        PassiveMultiplier() : Multiplier() {}

    public:
        virtual float GetValue(Action* action);
    };

}