#pragma once

#include "ActionFactory.h"

namespace ai
{
    class WarriorActionFactory : public ActionFactory
    {
    public:
        WarriorActionFactory(PlayerbotAIFacade* const ai) : ActionFactory(ai) {}

    public:
        virtual Action* createAction(const char* name);
    };
}