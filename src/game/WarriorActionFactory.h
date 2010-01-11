#pragma once

#include "ActionFactory.h"

namespace ai
{
    class WarriorActionFactory : public ActionFactory
    {
    public:
        WarriorActionFactory(PlayerbotAIFacade* const ai) : ActionFactory(ai) {}

    public:
        virtual Strategy* createStrategy(const char* name);
    };
}