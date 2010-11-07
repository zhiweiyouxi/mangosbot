#pragma once

#include "../ActionFactory.h"

namespace ai
{
    class PriestActionFactory : public ActionFactory
    {
    public:
        PriestActionFactory(AiManagerRegistry* const ai) : ActionFactory(ai) {}

    public:
        virtual Strategy* createStrategy(const char* name);
    };
}