#pragma once

#include "../ai/AiManagerRegistryAware.h"
#include "Action.h"
#include "Strategy.h"

#define CREATE_ACTION_RULE(actioname, clazz) \
    if (!strcmp(actioname, name)) \
        return new clazz(ai);


namespace ai
{
    class ActionFactory : public AiManagerRegistryAware
    {
    public:
        ActionFactory(AiManagerRegistry* const ai) : AiManagerRegistryAware(ai) {}
        virtual ~ActionFactory() {}

    public:
        virtual ActionNode* createAction(const char* name);
        virtual Strategy* createStrategy(const char* name);
    };
}