#pragma once

#include "Action.h"

namespace ai
{
    class FleeAction : public Action
    {
    public:
        FleeAction(PlayerbotAIFacade* const ai) : Action(ai) {}
        virtual void Execute();
    };
}