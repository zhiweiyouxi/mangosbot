#pragma once

#include "ActionFactory.h"

namespace ai
{
    class PriestActionFactory : public ActionFactory
    {
    public:
        PriestActionFactory(PlayerbotAIFacade* const ai) : ActionFactory(ai) {}

    public:
        virtual Strategy* createStrategy(const char* name);
    };
}