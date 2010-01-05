#pragma once

#include "ActionFactory.h"

namespace ai
{
    class HunterActionFactory : public ActionFactory
    {
    public:
        HunterActionFactory(PlayerbotAIFacade* const ai) : ActionFactory(ai) {}

    public:
        virtual Strategy* createStrategy(const char* name);
    };
}