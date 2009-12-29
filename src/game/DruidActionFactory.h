#pragma once

#include "ActionFactory.h"

namespace ai
{
    class DruidActionFactory : public ActionFactory
    {
    public:
        DruidActionFactory(PlayerbotAIFacade* const ai) : ActionFactory(ai) {}

    public:
        virtual Action* createAction(const char* name);
    };
}