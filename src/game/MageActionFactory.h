#pragma once

#include "ActionFactory.h"

namespace ai
{
    class MageActionFactory : public ActionFactory
    {
    public:
        MageActionFactory(AiManagerRegistry* const ai) : ActionFactory(ai) {}

    public:
        virtual Strategy* createStrategy(const char* name);
    };
}