#pragma once

#include "ActionFactory.h"

namespace ai
{
    class PaladinActionFactory : public ActionFactory
    {
    public:
        PaladinActionFactory(AiManagerRegistry* const ai) : ActionFactory(ai) {}

    public:
        virtual Strategy* createStrategy(const char* name);
    };
}