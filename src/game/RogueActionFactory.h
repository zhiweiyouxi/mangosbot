#pragma once

#include "ActionFactory.h"

namespace ai
{
    class RogueActionFactory : public ActionFactory
    {
    public:
        RogueActionFactory(AiManagerRegistry* const ai) : ActionFactory(ai) {}

    public:
        virtual Strategy* createStrategy(const char* name);
    };
}