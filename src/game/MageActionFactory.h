#pragma once

#include "ActionFactory.h"

namespace ai
{
    class MageActionFactory : ActionFactory
    {
    public:
        MageActionFactory(PlayerbotAIFacade* const ai) : ActionFactory(ai) {}

    public:
        virtual Action* createAction(const char* name);
    };
}