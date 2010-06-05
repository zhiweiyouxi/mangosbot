#pragma once

#include "../ActionFactory.h"

namespace ai
{
    class ShamanActionFactory : public ActionFactory
    {
    public:
        ShamanActionFactory(AiManagerRegistry* const ai) : ActionFactory(ai) {}

    public:
        virtual Strategy* createStrategy(const char* name);
    };
}