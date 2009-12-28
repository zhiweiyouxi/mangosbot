#pragma once
#include "Action.h"

namespace ai 
{
    class Multiplier
    {
    public:
        Multiplier() {}
        virtual ~Multiplier() {}

    public:
        virtual float GetValue(Action* action) { return 1.0f; }
    };

}