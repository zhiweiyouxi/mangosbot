#pragma once

#include "Multiplier.h"

namespace ai
{
    class FrostMageMultiplier : public Multiplier
    {
    public:
        FrostMageMultiplier() : Multiplier() {}

    public:
        virtual float GetValue(Action* action);
    };
}